import random
import math

#iterative euclidean algorithm for gcd
def gcd(a, b) :
	while a != b :
		if a > b :
			a = a - b
		else :
			b = b - a
	return a

def file_log(lines):
    f = open("Output.txt", "a")
    for line in lines:
        f.write(line + '\n')
    f.write('\n')
    f.close()
    return

def is_sq(num) :
	chk = math.sqrt(num)
	if math.ceil(chk) == math.floor(chk) :
		return True
	else :
		return False

def prime_factors(num) :
	pf = []
	if(num % 2 == 0) :
		pf.append(2)
	while(num % 2==0) :
		num = num / 2
	for i in range(3,math.ceil(math.sqrt(num))) :
		if(num % i == 0) :
			pf.append(i)
		while(num % i == 0) :
			num = num / i
	if(num > 2) :
		pf.append(int(num))
	return pf


def isSmooth(num, b, fb) :
	pf = prime_factors(num)
	print
	for i in pf :
		if i > b :
			return False
	return True


def identity_matrix(height):
	return [[1 if i == j else 0 for j in range(height)] for i in range(height)]


#getting a set of vectors from vector_list
#where multiplication of corresponding Q(a[i])s forms a perfect square  
def find_linear_combination(vector_list):
	height = len(vector_list)
	width = len(vector_list[0])
	combinations = identity_matrix(height)

	for offset in range(width):
		if vector_list[offset][offset] == 0:
			for x in range(width):
				if vector_list[offset][x] != 0:
					break
			else:
				#executed only when for loop does not break
				return combinations[offset]

			for y in range(offset + 1, height):
				if vector_list[y][offset] != 0:
					vector_list[y], vector_list[offset] = vector_list[offset], vector_list[y]
					combinations[y], combinations[offset] = combinations[offset], combinations[y]
					break
			else:
				#executed only when for loop does not break
				continue 

		for y in range(offset + 1, height):
			if vector_list[y][offset] == 0:
				continue
			for x in range(width):
				vector_list[y][x] *= -1
				vector_list[y][x] += vector_list[offset][x]
				vector_list[y][x] %= 2

			for x in range(height):
				combinations[y][x] *= -1
				combinations[y][x] += combinations[offset][x]
				combinations[y][x] %= 2
	print(combinations)
	#file_log(combinations)
	return combinations[-1]


#only for odd_primes and 2
def check_quad_residue(num, p) :
	if num == 1 and p == 2 :
		return True

	if num % p == 0 :
		return False
	else :
		res = num ** ((p - 1) / 2)
		res = res % p
		if res == 1 :
			return True
		else :
			return False

#naive method of checking if number is prime
def check_prime(num) :
	if num == 2 :
		return True
	if num % 2 == 0 :
		return False
	mx = math.ceil(math.sqrt(num))
	for i in range(2, mx) :
		if num % i == 0 :
			return False
	return True


#n is the number to be factorized and b is the bound
def quad_sieve(n, b) :
	#populating the factor base
	lines=[]
	factor_base = [-1]

	for i in range(2, b+1) :
		if check_prime(i) :
			mod = n % i
			if check_quad_residue(mod, i) :
				factor_base.append(i)

	fb_len = len(factor_base)
	print('Factor Base')
	lines.append('Factor Base')
	print(factor_base)
	lines.append(str(factor_base))
	q = []
	a = []
	i = 1
	while len(a) != fb_len :
		#root(n) + i
		temp = i + math.floor(math.sqrt(n))
		#Q(a[i]) = a[i]^2 - n
		q_temp = temp ** 2 - n
		if isSmooth(abs(q_temp), b, factor_base) :
			q.append(q_temp)
			a.append(temp)

		if len(q) == fb_len :
			break

		#root(n) - i
		temp = -i + math.floor(math.sqrt(n))
		#Q(a[i]) = a[i]^2 - n 
		q_temp = temp ** 2 - n
		if isSmooth(abs(q_temp), b, factor_base) :
			q.append(int(q_temp))
			a.append(temp)
		i += 1

	print('Numbers close to n^(1/2)')
	lines.append('Numbers close to n^(1/2)')
	print(a)
	lines.append(str(a))
	print(str(b)+'-Smooth Q(a[i]) = a[i] ^ 2 - n')
	lines.append(str(b)+'-Smooth Q(a[i]) = a[i] ^ 2 - n')
	print(q)
	lines.append(str(q))

	#exponent vectors
	exp_vec = []
	for i in range(len(q)) :
		vec = [-1 for _ in range(len(factor_base))]
		num = q[i]
		if q[i] < 0 :
			vec[0] = 1
			num = abs(num)
		else :
			vec[0] = 0

		for j in range(1, len(factor_base)) :
			count = 0
			while num % factor_base[j] == 0 :
				count += 1
				num = num / factor_base[j]
			count = count % 2
			vec[j] = count
		exp_vec.append(vec)
	print('Exponent vector')
	lines.append('Exponent vector')
	for row in exp_vec :
		print(row)
		lines.append(str(row))

	
	lc_list = find_linear_combination(exp_vec)
	x = 1
	y2 = 1
	print()
	lines.append("")
	print('Exponent vectors chosen are for, ')
	lines.append('Exponent vectors chosen are for, ')
	for i in range(len(lc_list)) :
		if lc_list[i] == 1 :
			print('a[i] = ' + str(a[i]) + '  Q(a[i]) = ' + str(q[i]))
			lines.append('a[i] = ' + str(a[i]) + '  Q(a[i]) = ' + str(q[i]))
			x *= a[i]
			y2 *= q[i]
	y = int(math.sqrt(y2))
	x = x % n
	y = y % n
	print(x, y)
	lines.append(str(x)+","+str(y))
	f = int(gcd(x - y, n))
	g = int(gcd(x + y, n))
	print(f, g)
	lines.append(str(f)+","+str(g))
	file_log(lines)

def main():
    n = int(input("Enter the positive integer n: "))
    b = int(input("Enter the positive integer : "))
    statements = list()
    if (n <= 0):
        statements.append((str(n) + " is not positive"))
        file_log(lines)
        return 0
    if (n == 1):
        statements.append((str(n) + " is a unique number and dosent have prime factors."))
        file_log(lines)
        return 0
    if (n == 2):
        statements.append((str(n) + " is the only prime factor of 2."))
        file_ops(lines)
        return 0  
    quad_sieve(n,b)

if __name__=='__main__':
    main()






