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


#
# Start by moving through spaces.
# In normal mode, echo back characters.
#   When we hit a space, echo the space and move through spaces and switch mode to seeking
# In seeking mode, move forward until there is a space, save this point, then move through all spaces and save the position as the reset position then switch into reverse mode from the save point
# In reverse mode, read and print characters moving backwards until hitting a space. When there is a space switch back to normal mode at the reset_position
#
class OddWord
  def initialize(f, dm=false)
    @file = f
    @mode = :normal
    @offset = 0
    @reset_point = 0
    @result_string = ""
    @debug_mode = dm
  end

  def run
    consume_spaces!

    while (ch = File.read(@file, 1, @offset)) != nil
      debug!

      if ch == "."
        _print "."
        done
      end

      if @mode == :normal
        _print ch
        if ch == " "
          consume_spaces!
          @mode = :seeking
        else
          @offset += 1
        end
      elsif @mode == :seeking
        if ch == " "
          # Done seeking, time to reverse
          @reverse_point = @offset - 1
          consume_spaces!
          @reset_point = @offset
          @offset = @reverse_point
          @mode = :reverse
        else
          @offset += 1
        end
      else # @mode == :reverse
        if ch == " "
          _print ch
          @offset = @reset_point
          @mode = :normal
        else
          _print ch
          @offset -= 1
        end
      end
    end

    done
  end

  def done
    if @debug_mode
      puts @result_string
    else
      puts ""
    end

    exit
  end

  def _print(ch)
    if @debug_mode
      @result_string += ch
    else
      print ch
    end
  end
  # Moves the offset pointer to the first non-space character
  def consume_spaces!
    while (ch = File.read(@file, 1, @offset)) == " "
      debug!
      @offset += 1
    end
  end

  def debug!
    return unless @debug_mode

    puts File.read(@file)
    (0...@offset).each { |x| print " " }
    print case @mode
          when :normal
            "n"
          when :seeking
            "s"
          when :reverse
            "r"
          else
            "?"
          end
    puts ""
  end
end

OddWord.new(file, false).run
