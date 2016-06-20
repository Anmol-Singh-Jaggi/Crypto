import sys

p1=0;p2=0 # p1 and p2 are the 2 primes...
n=0;phi_n=0 # n = p1*p2 ; phi_n is the Euler Totient Function value of n...
e=0;d=0 # e = Public Key exponent ; d = Private Key exponent

# The list of all the allowed characters in the input message...
alphabet="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz _"

def weight(c):
    # Returns the equivalent numerical value of the character 'c' in the alphabet ...
    # That is, it returns the index of the character 'c' in the alphabet string...
    global alphabet
    for i in xrange(len(alphabet)):
        if alphabet[i]==c:
            return i
    if i==len(alphabet):
        print "The message contains an illegal alphabet - '%c'\n",c
        sys.exit(1)

def gcd(a,b):
    # Returns the Greatest Common Divisor of integers 'a' and 'b'...
    if b==0:
        return a
    return gcd(b,a%b)

def mulmod(a,b,mod):
    # Returns (a*b)%mod...
    ans=0
    a%=mod
    while(b):
        if(b&1):
            ans=(ans+a)%mod
        a=(a*2)%mod
        b=b/2
    return ans

def powmod(a,b,mod):
    # Returns (a^b)%mod...
    ans=1
    while(b):
        if(b&1):
            ans=mulmod(ans,a,mod)
        a=mulmod(a,a,mod)
        b=b/2
    return ans

def smallest_coprime(num):
    # Returns the smallest number coprime to num...
    i=3
    while i<num:
        if(gcd(i,num)==1):
            return i
        i=i+1

def extended_gcd(a,b):
    coeffa=[1,0]
    coeffb=[0,1]
    temp=[0,0]
    q=r=0
    while(1):
        q=a/b
        r=a%b
        temp[0]=coeffb[0]
        temp[1]=coeffb[1]
        coeffb=[coeffa[0]-q*coeffb[0],coeffa[1]-q*coeffb[1]]
        coeffa[0]=temp[0]
        coeffa[1]=temp[1]
        a=b;
        b=r;
        if(r==0):
            break
    return coeffa

def inverse_mod(n,mod):
    # Returns (ans = inverse of "n" modulo "mod") such that (n*ans)%mod = 1...
    if gcd(n,mod)!=1:
        print "The 2 numbers ",n," and ",mod," are not coprime!!"
        sys.exit(1)
    return (extended_gcd(n,mod)[0]+mod)%mod

def init():
    # Initializes all the necessary variables...
    global p1,p2,n,phi_n,e,d
    n=p1*p2
    print "\"n\" = ",p1," * ",p2," = ",n
    phi_n=n-(p1+p2-1)
    print "Phi(n) = ",phi_n
    e=smallest_coprime(phi_n)
    print "\"e\" is selected to be = ",e
    d=inverse_mod(e,phi_n)
    print "\"d\" = inverse of ",e," mod ",phi_n," = ",d,"\n"
    print "Public key  -> (e,n) = ",[e,n]
    print "Private key  -> (d,n) = ",[d,n]

def RSA_encrypt(digest,power,N):
    # Returns (digest^power)%N
    return powmod(digest,power,N)

def encode(message):
    # Converts message into a number ( called "digest" )...
    # Considers message to be a number written in base - len(aplhabet)...
    # So it converts number in base-len(aplhabet) to its base-10 representation...
    global alphabet
    base=1;digest=0
    for i in xrange(len(message)-1,-1,-1):
        digest+=base*(weight(message[i]))
        base*=len(alphabet)
    return digest

def decode(digest):
    # Converts the digest back into a string...
    # Converts base-10 number back into its base-128 form...
    global alphabet
    message=""
    while(1):
        message=message+alphabet[digest%len(alphabet)]
        digest/=len(alphabet)
        if(digest==0):
            break
    return message[::-1] # Reverse of message...

def main():
    global p1,p2,n,phi_n,e,d
    print "Enter 2 space-separated different prime numbers"
    p1,p2=map(int,raw_input().split())
    init()
    print "Enter message to encrypt  "
    message=raw_input()
    m=encode(message)
    print "\nThe encoded message is  - ",m
    if(m>n):
        print "\n\nError : The encoding of the message ",m," has a value greater than the mod ",n," .\nEither decrease the length of the message or increase the length of the prime numbers.\n\nExiting!!\n"
        sys.exit(1)
    m=RSA_encrypt(m,e,n)
    print "The encrypted message is - ",m
    m=RSA_encrypt(m,d,n)
    print "The decrypted message is - ",m,"\n"
    message=decode(m)
    print "The decoded message is - ",message

if __name__=="__main__":
    main()
