from Linked_list import LinkedList, Node

if __name__ == '__main__':

    stringList = LinkedList()
    # Prepare a test set
    s1 = Node("afe")
    s2 = Node("aBc")
    s3 = Node("ABC")
    # Prepare a test object
    sTest = Node("afe")
    # Prepare the list
    stringList.sorted_list_insert(s1)
    stringList.sorted_list_insert(s2)
    stringList.sorted_list_insert(s3)
    # Print initial list
    stringList.print_list()
    # add the test object
    stringList.sorted_list_insert(sTest)
    # Display the list again
    stringList.print_list()
    # Remove a certain node
    stringList.sorted_list_remove(s1)
    stringList.print_list()

