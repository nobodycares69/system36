p=int(input("The value of p: "))
q=int(input("The value of q: "))
a=int(input('The Private Key a for Alice is: '))
b=int(input('The Private Key b for Bob is: '))
print("Generated key for Alice: ",pow(q,a)%p)
R=pow(q,a)%p
print("Generated key for Bob: ",pow(q,b)%p)
S=pow(q,b)%p
print("Secret key for the Alice is: ",pow(S,a)%p)
Rk=pow(S,q)%p
print("Secret Key for the Bob is: ",pow(R,b)%p)
Sk=pow(R,b)%p