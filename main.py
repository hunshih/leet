import search

def testBinSearch():
    ary = [1,2,3,4,5,6,7,8,9,10,19]
    print("===test 1===")
    output = search.binSearch(ary, 3)
    print("result: {}".format(output))
    print("===test 2===")
    output = search.binSearch(ary, 100)
    print("result: {}".format(output))

def testFirstOccur():
    ary = [1,2,3,4, 4, 4, 4,5,6,7,8,9,10, 10, 10 ,19]
    print("===test 1===")
    output = search.binSearch(ary, 10)
    print("result: {}".format(output))
    print("===test 2===")
    output = search.binSearch(ary, 4)
    print("result: {}".format(output))
    print("===test 3===")
    output = search.binSearch(ary, 100)
    print("result: {}".format(output))

def main():
    
    # test vanilla binary search
    # testBinSearch()

    # test finding first occurence
    testFirstOccur()

if __name__ == "__main__":
    main()