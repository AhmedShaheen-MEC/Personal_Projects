import unittest

# Import test modules
from Linked_list import LinkedList, Node


class Test00Node(unittest.TestCase):

    @classmethod
    def setUpClass(cls):

        cls.nodeTestObject = Node("A")

    def test_data(self):

        self.assertEqual(self.nodeTestObject.data,"A")


class Test01LinkedList(unittest.TestCase):

    def setUp(self):

        print("\n----New test----\nList before the test:")
        self.stringList = LinkedList()
        # Prepare a test set
        s1 = Node("abc")
        s2 = Node("aBc")
        s3 = Node("ABC")
        self.stringList.sorted_list_insert(s1)
        self.stringList.sorted_list_insert(s2)
        self.stringList.sorted_list_insert(s3)
        self.stringList.print_list()

    def tearDown(self):

        print("\n----Test finished----\nList after the test:")
        self.stringList.print_list()
        print("------------------------------------------------")

    def test_add_smallest_string(self):

        smallest_string = Node("AAA")

        self.assertEqual(self.stringList.sorted_list_insert(smallest_string), 0)
        self.assertEqual(self.stringList.head, smallest_string)

    def test_add_largest_string(self):

        largest_string = Node("zzz")
        self.assertEqual(self.stringList.sorted_list_insert(largest_string), 0)
        self.assertEqual(self.stringList.head.next.next.next, largest_string)

        self.stringList.print_list()

    def test_add_intermediate_string(self):

        intermediate_string = Node("aBc")
        expected_location = 1
        self.assertEqual(self.stringList.sorted_list_insert(intermediate_string), 0)

        temp = self.stringList.head
        index = 0
        while temp is not None:

            if temp != intermediate_string:
                index = index + 1
                temp = temp.next
                continue
            else:
                break
        self.assertEqual(index,expected_location)

    def test_sorting_order(self):

        temp = self.stringList.head
        while temp.next is not None:

            self.assertLessEqual(temp.data, temp.next.data)
            temp = temp.next

    def test_remove_head_node(self):

        temp = self.stringList.head
        second_string = self.stringList.head.next

        self.assertEqual(self.stringList.sorted_list_remove(temp), 0)
        self.assertLessEqual(self.stringList.head.data, second_string.data)

    def test_remove_not_in_the_list(self):

        temp = Node("Not in the list")
        self.assertEqual(self.stringList.sorted_list_remove(temp), -1)

    def test_remove_none(self):

        temp = None
        self.assertEqual(self.stringList.sorted_list_remove(temp), -1)

    def test_add_none(self):

        temp = None
        self.assertEqual(self.stringList.sorted_list_insert(temp), -1)