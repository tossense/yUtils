Object_to_pod = Hash.new
Text_sum = Hash.new(0)
Text_scope = Array.new

# # Object files:
# [  0] linker synthesized
# [  1] dtrace
# [  2] /Users/jenkins/jenkins-slave-home/workspace/imeituan/app-store-build/hyperlane_sandbox/build/Build/Intermediates/ArchiveIntermediates/imeituan/IntermediateBuildFilesPath/imeituan.build/Release-iphoneos/imeituan.build/Objects-normal/arm64/main.o
# [  3] /Users/jenkins/jenkins-slave-home/workspace/imeituan/app-store-build/hyperlane_sandbox/build/Build/Intermediates/ArchiveIntermediates/imeituan/IntermediateBuildFilesPath/imeituan.build/Release-iphoneos/imeituan.build/Objects-normal/arm64/imeituan_vers.o
# [  4] /Users/jenkins/jenkins-slave-home/workspace/imeituan/app-store-build/Pods/ADFlowCalendarView/bin/libADFlowCalendarView.a(ADFlowCalendarAppearance.o)
# ...
# [11735] /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/arc/libarclite_iphoneos.a(arclite.o)
# [11736] /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS10.0.sdk/usr/lib/libobjc.tbd
# [11737] /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS10.0.sdk/usr/lib/libSystem.tbd
# [11738] /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS10.0.sdk/System/Library/Frameworks//CoreFoundation.framework/CoreFoundation.tbd
# [11739] /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS10.0.sdk/System/Library/Frameworks//MapKit.framework/MapKit.tbd
def self.do_object(line)
  return if line[0] == '#'
  m = /\[(.+)\].+/.match(line)
  #puts line
  object = m[1].to_i
  m = /\[(.+)\].+\/Pods\/([^\/]+)\/.+/.match(line)  
  pod = m[2] rescue nil
  unless pod
    m = /\[(.+)\].+\/([^\/]+)\.a\(.+\)/.match(line)
    pod = m[2] rescue nil
  end
  if object and pod
    Object_to_pod[object] = pod
  else
    Object_to_pod[object] = line.split.last
  end
  puts line unless object
end

# 0x100004240 0x03B54D68  __TEXT  __text
# 0x103B58FA8 0x00004230  __TEXT  __stubs
# 0x103B5D1D8 0x0000420C  __TEXT  __stub_helper
# 0x103B613F0 0x00007FA8  __TEXT  __const
# 0x103B69398 0x0002691E  __TEXT  __ustring
# 0x103B8FCB6 0x0000037B  __TEXT  __dof_RACSignal
# 0x103B90031 0x000002E8  __TEXT  __dof_RACCompou
# 0x103B9031C 0x000DFB84  __TEXT  __unwind_info
# 0x103C6FEA0 0x0000012C  __TEXT  __eh_frame
# 0x103C70000 0x00001498  __DATA  __got
# 0x103C71498 0x00002C20  __DATA  __la_symbol_ptr
# 0x103C740B8 0x000009C8  __DATA  __mod_init_func
# 0x103C74A80 0x00000008  __DATA  __mod_term_func
# 0x103C74AC0 0x00237C78  __DATA  __const
def self.do_sections(line)
  arr = line.split
  return unless arr[2]
  return unless arr[2] == '__TEXT'
  offset = arr[0].to_i(16)
  length = arr[1].to_i(16)
  Text_scope.push({'l'=> offset, 'r'=> offset + length}) # [l, r)
end

def self.is_text_symbol?(offset)
  Text_scope.each do |pair|
    if offset >= pair['l'] and offset < pair['r']
      return true
    end
  end
  return false
end

# # Symbols:
# # Address Size      File  Name
# 0x100004240 0x00000050  [  2] _disable_gdb
# 0x100004290 0x00000084  [  2] _main
# 0x100004314 0x00000018  [  4] -[ADFlowCalendarAppearance contentInsets]
# 0x10000432C 0x00000018  [  4] -[ADFlowCalendarAppearance setContentInsets:]
# 0x100004344 0x00000010  [  4] -[ADFlowCalendarAppearance dayPadding]
def self.do_symbols(line)
  return if line[0] == '#'
  #puts line
  arr = line.split
  return unless arr.length > 2
  offset = arr[0].to_i(16)
  #length = arr[1].to_i(16)
  return unless is_text_symbol?(offset)

  symbol_size = arr[1].to_i(16)
  object = if arr[2] == '['
    arr[3].chop.to_i
  else
    arr[2].reverse.chop.reverse.chop.to_i
  end
  pod = Object_to_pod[object]
  Text_sum[pod] = Text_sum[pod] + symbol_size
  #puts line unless pod
end

status = 'start'

linkmap_file = ARGV[0]

# cat imeituan-LinkMap-normal-arm64.txt | grep "^#" -n
# 1:# Path: /Users/jenkins/jenkins-slave-home/workspace/imeituan/app-store-build/hyperlane_sandbox/build/Build/Intermediates/ArchiveIntermediates/imeituan/IntermediateBuildFilesPath/imeituan.build/Release-iphoneos/imeituan.build/Objects-normal/arm64/imeituan
# 2:# Arch: arm64
# 3:# Object files:
# 11744:# Sections:
# 11745:# Address Size      Segment Section
# 11783:# Symbols:
# 11784:# Address Size      File  Name
# 990600:# Dead Stripped Symbols:
# 990601:#          Size      File  Name
File.read(linkmap_file).lines.each do |line|
  line = line.force_encoding("iso-8859-1").strip
  case status
  when 'start'
    nil
  when 'object'
    do_object(line)
  when 'sections'
    do_sections(line)
  when 'symbols'
    do_symbols(line)
  else
    nil
  end

  status = case line
    when '# Object files:'
      'object'
    when '# Sections:'
      'sections'
    when '# Symbols:'
      'symbols'
    when '# Dead Stripped Symbols:'
      'dead'
    else
      status
  end
end
#puts Text_scope
puts Text_sum.map{|k,v| puts "#{k}\t#{v}"; v}.reduce(0, :+)