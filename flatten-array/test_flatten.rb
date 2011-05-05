begin
  require 'minitest/autorun'
  require 'minitest/unit'
rescue LoadError
  warn "Must install minitest gem (it comes standard in Ruby 1.9)"
  exit 1
end

# Load array extension for "my_flatten".
require File.join(File.dirname(__FILE__), "flatten")
class Array
  include TobyArrayExt
end

#
# Tested on MRI Ruby 1.9.2 and 1.8.7
#
class TestFlatten < MiniTest::Unit::TestCase

  #
  # Append-until-flat implementation.
  #

  def test_append_no_change
    a = [1, 2, 3, 4]
    assert_equal a, a.my_flatten_append
  end

  def test_append_one_level
    a = [[1,2], 3, 4]
    assert_equal [3, 4, 1, 2], a.my_flatten_append
  end

  def test_append_multilevel
    a = [[[1, 2], 3], [4, 5]]
      # These are the intermediate steps:
      # [[4, 5], [1, 2], 3]
      # [[1, 2], 3, 4, 5]
      # [3, 4, 5, 1, 2]
    assert_equal [3, 4, 5, 1, 2], a.my_flatten_append
  end

  def test_append_nil
    a = [nil, [1, 2], [3, nil], 4]
      # These are the intermediate steps:
      # [nil, [3, nil], 4, 1, 2]
      # [nil, 4, 1, 2, 3, nil]
    assert_equal [nil, 4, 1, 2, 3, nil], a.my_flatten_append
  end


  #
  # Order-preserving implementation.
  #

  def test_inorder_no_change
    a = [1, 2, 3, 4]
    assert_equal a, a.my_flatten_inorder
  end

  def test_inorder_one_level
    a = [[1,2], 3, 4]
    assert_equal [1, 2, 3, 4], a.my_flatten_inorder
  end

  def test_inorder_multilevel
    a = [[[1, 2], 3], [4, 5]]
    assert_equal [1, 2, 3, 4, 5], a.my_flatten_inorder
  end

  def test_inorder_nil
    a = [nil, [1, 2], [3, nil], 4]
    assert_equal [nil, 1, 2, 3, nil, 4], a.my_flatten_inorder
  end

  #
  # Stack implementation (also order-preserving).
  #

  def test_inorder_stack_no_change
    a = [1, 2, 3, 4]
    assert_equal a, a.my_flatten_inorder_stack
  end

  def test_inorder_stack_one_level
    a = [[1,2], 3, 4]
    assert_equal [1, 2, 3, 4], a.my_flatten_inorder_stack
  end

  def test_inorder_stack_multilevel
    a = [[[1, 2], 3], [4, 5]]
    assert_equal [1, 2, 3, 4, 5], a.my_flatten_inorder_stack
  end

  def test_inorder_stack_nil
    a = [nil, [1, 2], [3, nil], 4]
    assert_equal [nil, 1, 2, 3, nil, 4], a.my_flatten_inorder_stack
  end

end
