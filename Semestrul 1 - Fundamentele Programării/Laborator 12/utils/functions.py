import random
import string

def string_generator(lg):
    return ''.join(random.choice(string.ascii_uppercase) for _ in range(lg))

def minIndex(a, i, j):
    if i == j:
        return i
    # Find minimum of remaining elements
    k = minIndex(a, i + 1, j)
    # Return minimum of current
    # and remaining.
    return (i if a[i][2] < a[k][2] else k)

def recurSelectionSort(a, n, index=0):
    # Return when starting and
    # size are same
    if index == n:
        return -1

    # calling minimum index function
    # for minimum index
    k = minIndex(a, index, n - 1)

    # Swapping when index and minimum
    # index are not same
    if k != index:
        a[k], a[index] = a[index], a[k]

    # Recursively calling selection
    # sort function
    recurSelectionSort(a, n, index + 1)

def selectionSort(arr, key=None, reverse=False, cmp=None):
    n = len(arr)

    for i in range(n):
        # Find the index of the minimum (or maximum) element in the unsorted part
        min_index = i
        for j in range(i + 1, n):
            if (key(arr[j]) if key else arr[j]) < (key(arr[min_index]) if key else arr[min_index]):
                min_index = j

        # Swap the found minimum (or maximum) element with the first element
        arr[i], arr[min_index] = arr[min_index], arr[i]

    # Apply reverse if specified
    if reverse:
        arr.reverse()

    # Apply custom comparison function if specified
    if cmp:
        arr.sort(cmp=cmp)

    return arr

def cocktailSort(arr, key=None, reverse=False, cmp=None):
    """
    Perform cocktail shaker sort on the input list.

    Parameters:
    - arr: The list to be sorted.
    - key: A function to extract a comparison key from each element.
    - reverse: A boolean indicating whether to sort in reverse order.
    - cmp: A custom comparison function.

    Returns:
    None (modifies the input list in place).
    """
    n = len(arr)
    swapped = True
    start = 0
    end = n - 1

    while (swapped == True):
        # Reset the swapped flag on entering the loop
        swapped = False

        # Forward pass: Similar to bubble sort
        for i in range(start, end):
            if (key(arr[i]) if key else arr[i]) > (key(arr[i + 1]) if key else arr[i + 1]):
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True

        # If nothing moved, the list is sorted
        if not swapped:
            break

        # Reset the swapped flag before the reverse pass
        swapped = False

        # Move the end point back by one, because the item at the end is in its rightful spot
        end = end - 1

        # Reverse pass: Similar to bubble sort but in the opposite direction
        for i in range(end - 1, start - 1, -1):
            if (key(arr[i]) if key else arr[i]) > (key(arr[i + 1]) if key else arr[i + 1]):
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True

        # Move the start point forward by one, because the item at the start is in its rightful spot
        start = start + 1

    # Apply reverse if specified
    if reverse:
        arr.reverse()

    # Apply custom comparison function if specified
    if cmp:
        arr.sort(cmp=cmp)

    return arr
