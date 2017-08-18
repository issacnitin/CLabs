import itertools
def sub_sets(my_list, n):
    temp=list(itertools.combinations(my_list, n))
    list_of_lists = [list(elem) for elem in temp]
    return list_of_lists
    

n = int(input())
inputList = input()
inputList = list(map(int, inputList.split()))
arrList = sub_sets(inputList, 0)
for i in range(1, len(inputList)+1):
    arrList += sub_sets(inputList, i)

masterCount = 0
for arr in arrList:
    count = 64
    print(arr)
    while arr != []:
        el = arr[0]
        s=[el]
        arr=arr[1:]
        while s != []:
            el=s[0]
            s=s[1:]
            lst=[]
            for x in arr:
                if x & el != 0:
                    el = el|x
                    s.append(el)
                    lst.append(x)
                    arr.remove(x)
        for index in range(0, 65):
            if el & (1<<index):
                count -= 1
        count += 1
    print(count)
    masterCount += count
            
print(masterCount)
