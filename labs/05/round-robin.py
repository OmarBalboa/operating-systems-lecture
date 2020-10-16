#Omar Alejandro Balboa Lara
#A00825034
#Graphic: https://drive.google.com/file/d/1KUS5JwFe6T5_1_xd-X1X_V_r56aHie8l/view?usp=sharing

import matplotlib.pyplot as plt

#I had some problems with the quantum and quantum_max, fixed it with the int() function
quantum = int(input("Enter the initial quantum: "))
quantum_max = int(input("Enter the final quantum: "))
quantums = []
avg_turnaround_tms = []

processes =[2,3,4,12,8,5,6,1]
num_processes = len(processes)
q = []

while quantum <= quantum_max:

    context_switch = 2
    execution_time = 0
    avg_turnaround_tm = 0.0

    i = 0
    quantums.append(quantum)

    while i < len(processes):
        q.append(processes[i])
        i+=1
        
    while 0<len(q):
        current_process = q.pop(0)
        if current_process <= quantum:
            execution_time += current_process
        else:
            remain_time = current_process - quantum
            execution_time+=quantum
            execution_time+=context_switch
            q.append(remain_time)


    avg_turnaround_tm = float(execution_time)/float(num_processes)
    avg_turnaround_tms.append(avg_turnaround_tm)
    quantum+=1

#To print quantums and avg
print ("Quantums")
print (quantums)
print ("Avg Turnaround times:")
print (avg_turnaround_tms)
print("Initial processes")
print (processes)
#Create the graph and the title for it
plt.plot(quantums, avg_turnaround_tms)
plt.title('Quantum Time vs Turnaround Time')
plt.xlabel('Quantums')
plt.ylabel('Turnaround Time')
plt.show()
