#!/usr/bin/python

import sys, os, random, numpy, pdb

mat_size = 10
numbers = 1000000

def d_uniform(size, mx, step):
    flg = 0
    while 1:
        summ = 1
        l = []
        for i in range(size):
            if i == size - 1 and summ > 0.002:
                l.append(summ)
                return l
            x = random.uniform(0, 1) * mx
            summ -= x
            if summ <= 0:
                break
            else:
                l.append(x)
        mx -= step
        if mx == 0:
            return []

def print_2dlist(l):
    for line in l:
        for elem in line:
            print "%.3f" %elem,
        print ''


mat_event1 = \
 [
    [0.3, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2], \
    [0.2, 0.3, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0], \
    [0.0, 0.2, 0.3, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0], \
    [0.0, 0.0, 0.2, 0.3, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0], \
    [0.0, 0.0, 0.0, 0.2, 0.3, 0.5, 0.0, 0.0, 0.0, 0.0], \
    [0.0, 0.0, 0.0, 0.0, 0.2, 0.3, 0.5, 0.0, 0.0, 0.0], \
    [0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.3, 0.5, 0.0, 0.0], \
    [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.3, 0.5, 0.0], \
    [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.3, 0.5], \
    [0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2, 0.3]  \
  ]



if __name__ == "__main__":
    os.chdir('./out')
    l = []
    mat_event2 = []
    while len(l) == 0:
        l = d_uniform(mat_size, 1.0 / mat_size * 2, 0.01)
    #pdb.set_trace()
    for i in range(mat_size):
        mat_event2.append([])
        mat_event2[len(mat_event2) - 1].extend(l)
        l.insert(0, l[mat_size - 1])
        l.pop(mat_size)
    print_2dlist(mat_event2)
    
    math_events = []
    math_events.append(mat_event1)
    math_events.append(mat_event2)
    index = 0
    for i in range(0, len(math_events)):
        mat_event = math_events[i]
        hist_x = [0] * mat_size
        hist_event = [0] * mat_size

        mat_prob = [0.0] * mat_size
        for i in range(mat_size):
            mat_prob[i] = [0.0] * mat_size

        array_ksi = [0.0] * 500
        random.seed()

        for i in range(mat_size):
            mat_prob[i][0] = mat_event[i][0]
            for j in range(mat_size)[1:]:
                mat_prob[i][j] = mat_event[i][j] + mat_prob[i][j - 1]

        c_event = 0
        for k in range(numbers):
            tmp = random.uniform(0, 1)
            for i in range(mat_size):
                if tmp < mat_prob[c_event][i]:
                    c_event = i
                    while True:
                        ksi = random.uniform(0, 1)
                        ksi = -1.0 * numpy.log(ksi)
                        c_x = int(ksi / 0.7)
                        if c_x < mat_size:
                            break
                    hist_event[c_event] += 1
                    hist_x[c_x] += 1
                    break
            if k < 500:
                array_ksi[k] = ksi

        file = open('hist' + str(index), 'w')
        for i in range(mat_size):
            file.write(str(i + 1) + '\t' + str(hist_event[i]) + '\t'\
                       + str(hist_x[i]) + '\n')
        file.close()
        file = open('ksi' + str(index), 'w')
        for i in range(500):
            file.write(str(i + 1) + '\t' + repr(array_ksi[i]) + '\n')
        file.close()
        index += 1
