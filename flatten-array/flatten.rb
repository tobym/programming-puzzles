#
# Author: Toby Matejovsky
#
# Include this array extension in the Array class to get some pure-Ruby
# implementations of Array#flatten.
#
#   class Array
#     include TobyArrayExt
#   end
#
module TobyArrayExt
  #
  # Flattens an array by pushing non-flat elements onto the end of the list
  # until there are no more non-flat elements. Note this does not preserve
  # "in-place" order. Each non-flat element becomes one level more flat as it
  # is encountered and pushed onto the end of the array.
  #
  # See test_append_multilevel for a step-by-step of this process.
  #
  #   a = [[1, 2], 3, 4]
  #   a.flatten # => [3, 4, 1, 2]
  #
  def my_flatten_append
    dup.my_flatten_append!
  end

  # Flatten-by-appending that mutates self.
  def my_flatten_append!
    idx = 0
    while idx < length
      if at(idx).respond_to? :to_ary
        # If current element isn't flat, delete and move its flattened sub-
        # elements to the end.
        elm = delete_at idx
        push *(elm.to_ary)
      else
        idx += 1
      end
    end
    self
  end

  #
  # Given that order-preserving semantics are likely to be expected, here is
  # another flattening implementation that preserves "in-place" order.
  #
  #   a = [[1, 2], 3, 4]
  #   a.flatten # => [1, 2, 3, 4]
  #
  def my_flatten_inorder
    dup.my_flatten_inorder!
  end

  # Flatten-in-order that mutates self.
  def my_flatten_inorder!
    idx = 0
    while idx < length
      if at(idx).respond_to? :to_ary
        # If current element isn't flat, replace it with its own flattened sub-
        # elements.
        elm = delete_at idx
        insert idx, *(elm.to_ary)
      else
        idx += 1
      end
    end
    self
  end

  #
  # Another order-preserving array flatten implementation; this one uses a
  # stack.
  #
  def my_flatten_inorder_stack
    dup.my_flatten_inorder_stack!
  end

  # Flatten-in-order with stack that mutates self.
  def my_flatten_inorder_stack
    # Copy elements to a "source" that will feed flattened elements into self.
    src = dup
    clear

    while src.any?
      # Get next element.
      push src.shift
      if last.respond_to? :to_ary
        # If it's not flat, flatten once and stuff back into source.
        elm = pop
        src.unshift *(elm.to_ary)
      end
    end

    self
  end
end
