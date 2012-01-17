#
# Usage:
#   ruby odd_word.rb <path/to/input/file>
#
# Description:
#   Dijkstra's odd-word problem, see http://c2.com/cgi/wiki?OddWordProblem
#
# In:
#   "whats the matter with kansas."
# Out:
#   "whats eht matter htiw kansas."
#

# file = "input.txt"
file = ARGV.first
offset = 0
reset_point = 0

mode = :normal # :seeking, :reversing

while (ch = File.read(file, 1, offset)) != nil
  if ch == "."
    puts "."
    exit
  end

  if mode == :normal
    print ch
    offset += 1
    if ch == " "
      mode = :seeking
    end
  elsif mode == :seeking
    if ch == " "
      reset_point = offset
      offset -= 1
      mode = :reversing
    else
      offset += 1
    end
  elsif mode == :reversing
    if ch == " "
      print ch
      mode = :normal
      offset = reset_point + 1
    else
      print ch
      offset -= 1
    end
  end
end
