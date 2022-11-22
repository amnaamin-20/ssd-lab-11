
s =6
print ('multiplication of above number is',s * s)

num1 =1.5
num2 =6.3
sub =num2-num1
print('The subtraction of',num1,'from',num2,'is',sub)

numlist=[1,2,3,4,5,6,7,8]
print ('elements in list are:\ncolumn display:')
for x in numlist:
    print(x)
print ('row display:')
for x in numlist:
    print(x,end =' ')

numtuple=(10,20,30,40,50,60)
print('\nprinting tuple elements from indexes 2 to 5\n',numtuple[2:5])

#2D array printing and loop on basis of range
bookings = [[1, 10], [5, 10], [11, 20]]

for i in range(0, 3):
    print(bookings[i][0], " ", bookings[i][1])

#function creation


def most_frequent_elements_in_lis(elem_list, left, right, frequency):
    frequency_elements=[]
    checked_elements=[]
    for j in range(left, right):
        temp = elem_list[j]
        done = 0
      # print("\n", elem_list[j])
        count = 0
        for x in checked_elements:
            if x == temp:
                done = 1
        if done != 1:
            for k in range(left, right):
               if elem_list[k] == temp:
                   count += 1
            if count >= frequency:
               frequency_elements.append(temp)

        checked_elements.append(temp)
    print("part b's answer: ", frequency_elements)


lis = [2, 2, 4, 2, 4, 5, 6, 1, 1]
most_frequent_elements_in_lis(lis, 0, 5, 2)
