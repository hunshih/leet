import util

'''
Assuming ascending order

return: index of target, or -1 if not found
'''
def binSearch(ary, target):
    operation = 0
    left = 0
    right = len(ary)
    while left < right :
        operation += 1
        mid = (left + right)//2
        if target == ary[mid]:
            util.complexity(len(ary), operation, 1)
            return mid
        if ary[mid] > target:
            right = mid
        else :
            left = mid + 1
    util.complexity(len(ary), operation, 1)
    return -1

'''
Assuming ascending order

return: index of target, or -1 if not found
'''
def firstOccur(ary, target):
    operation = 0
    ans = -1
    left = 0
    right = len(ary)
    while left < right :
        operation += 1
        mid = (left + right)//2
        if target == ary[mid]:
            ans = mid
        if ary[mid] >= target:
            right = mid
        else :
            left = mid + 1
    util.complexity(len(ary), operation, 1)
    return ans