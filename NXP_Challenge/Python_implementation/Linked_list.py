class Node:

    def __init__(self,data):

        self.data = data
        self.next = None
        if type(data) is not str:
            raise Exception("Error, please use string data type")

        print("Node created with value: ",self.data)


class LinkedList:

    def __init__(self):

        self.head = None    # at the beginning list is empty

    def sorted_list_insert(self,node):

        # Check if the node was empty
        if node is None:
            print("Warning - Linked list insert: node is empty..!\n")
            return -1
        # Check if the list was empty
        if self.head is None:

            self.head = node
            node.next = None
            return 0
        # Iterate through the list until finding a larger string
        current_node = self.head
        while current_node is not None:

            # if the entered node has larger value, go to next node
            if node.data > current_node.data:

                prev = current_node
                current_node = current_node.next
                continue
            node.next = current_node
            # if the entered node has the smallest value
            if node.next == self.head:
                # switch the head node
                temp = self.head
                self.head = node
                self.head.next = temp
                return 0
            prev.next = node
            return 0
        # End of list is reached and there is no larger value string
        prev.next = node
        # next is none as this should be the last node in the list
        node.next = None
        return 0

    def sorted_list_remove(self,node):

        current_node = self.head
        # check if the entered node is empty
        if node is None:
            print("Warning - Linked list Remove: Node is empty..!\n")
            return -1
        # check if the head node the one which should be removed
        if self.head == node:
                self.head = node.next
                return 0
        # loop until find the node which should be removed
        while current_node is not None:
            if current_node.next == node:
                break
            current_node = current_node.next
        # if the node was not found, do nothing
        if current_node is None:
            print("Warning - Linked list Remove: Node is not in the list..!\n")
            return -1
        # re-arrange the list
        current_node.next = node.next
        return 0

    def print_list(self):

        current_node = self.head
        index = 0
        # loop until the end
        while current_node:

            print("String number:", index, "has a value of: ", current_node.data)
            current_node = current_node.next
            index = index + 1
