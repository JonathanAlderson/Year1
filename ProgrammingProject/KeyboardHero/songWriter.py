

#  time = N note 0
j = 500
for i in range(10000):
    if(i % 1000 == 0):
        print(str(i) + " = N 0 200")
        print(str(i+200) + " = N 1 200")
        print(str(i+400) + " = N 2 200")
        print(str(i+600) + " = N 3 200")
        print(str(i+800) + " = N 4 200")
for i in range(10000,20000):
    if(i % 500 == 0):
        print(str(i) + " = N 0 200")
        print(str(i+100) + " = N 1 200")
        print(str(i+200) + " = N 3 200")
        print(str(i+300) + " = N 2 200")
        print(str(i+400) + " = N 4 200")
