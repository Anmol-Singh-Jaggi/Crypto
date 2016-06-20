#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define all(x) x.begin(),x.end()
#define fastin std::ios::sync_with_stdio(false);cin.tie(NULL)
#define cout_precision(x) cout<<std::fixed<<setprecision(x)
using namespace std;
#ifdef DEBUG
#include <Debug.h>
#endif

long long p1, p2; // p1 and p2 are the 2 primes...
long long n, phi_n;
long long e, d;
const string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz _";

int weight( const char& c )
{
	for ( int i = 0; i < ( int )alphabet.size(); i++ )
	{
		if ( alphabet[i] == c )
		{
			return i;
		}
	}
	return -1;  // Should never be executed...
}
long long gcd( long long a, long long b )
{
	if ( b == 0 )
	{
		return a;
	}
	return gcd( b, a % b );
}


long long mulmod( long long a, long long b, const long long& mod ) // Calculate (a*b)%mod
{
	long long ans = 0;
	a %= mod;
	while ( b )
	{
		if ( b & 1 )
		{
			ans = ( ans + a ) % mod;
		}
		a = ( a << 1 ) % mod;
		b >>= 1;
	}
	return ans;
}

long long powmod( long long a, long long b, const long long& mod ) // Calculate (a^b)%mod
{
	long long ans = 1;
	while ( b )
	{
		if ( b & 1 )
		{
			ans = mulmod( ans, a, mod );
		}
		a = mulmod( a, a, mod );
		b >>= 1;
	}
	return ans;
}

long long find_coprime( const long long& num )
{
	long long i;
	for ( i = 2; i < num; i++ )
	{
		if ( gcd( i, num ) == 1 )
		{
			return i;
		}
	}
	return i;
}
pair<long long, long long> extended_gcd( long long a, long long b )
{
	pair<long long, long long> coeffa( 1, 0 ); // a=a(1) + b(0)
	pair<long long, long long> coeffb( 0, 1 ); // b=a(0) + b(1)
	pair<long long, long long> temp;
	long long q, r;
	do
	{
		q = a / b;
		r = a % b;
		temp = coeffb;
		coeffb = make_pair( coeffa.first - q * coeffb.first, coeffa.second - q * coeffb.second );
		coeffa = temp;
		a = b;
		b = r;
	}
	while ( r );
	return coeffa;
}

long long inverse_mod( long long a, long long b )
{
	assert( gcd( a, b ) == 1 );
	return ( extended_gcd( a, b ).first + b ) % b;
}

void init()
{
	n = p1 * p2;
	cout << "\"n\" = " << p1 << " * " << p2 << " = " << n << "\n\n";
	phi_n = n - ( p1 + p2 - 1 );
	cout << "Phi(n) = " << phi_n << "\n";
	e = find_coprime( phi_n );
	cout << "\"e\" is selected to be = " << e << "\n";
	d = inverse_mod( e, phi_n );
	cout << "\"d\" = inverse of " << e << " mod " << phi_n << " = " << d << "\n\n";
	cout << "Public key  -> (e,n) = (" << e << "," << n << ")\n";
	cout << "Private key  -> (d,n) = (" << d << "," << n << ")\n\n";
}

void RSA_encrypt( long long& message_encoding, const long long& power, const long long& N )
{
	message_encoding = powmod( message_encoding, power, N );
}

long long encode( const string& message )
{
	long long base = 1, ans = 0;
	for ( int i = message.size() - 1; i >= 0; i-- )
	{
		ans += base * ( weight( message[i] ) );
		base *= alphabet.size();
		debug( base );
	}
	return ans;
}

string decode( long long m )
{
	string ans;
	do
	{
		ans.push_back( alphabet[m % alphabet.size()] );
		m /= alphabet.size();
	}
	while ( m );
	reverse( all( ans ) );
	return ans;
}
int main()
{
	cout << "Enter 2 prime numbers [ <10^6 ] ";
	cin >> p1 >> p2;
	cin.get();
	init();
	cout << "Enter message to encrypt - ";
	string message;
	getline( cin, message );
	long long m = encode( message );
	cout << "\nThe encoded message is  - " << m << "\n";
	if ( m > n )
	{
		cout << "\n\nError : The encoding of the message has a value greater than the mod.\nEither decrease the length of the message or increase the length of the prime numbers.\n\nExiting!!\n\n";
		return 1;
	}
	RSA_encrypt( m, e, n );
	cout << "The encrypted message is - " << m << "\n";
	RSA_encrypt( m, d, n );
	cout << "The decrypted message is - " << m << "\n\n";
	message = decode( m );
	cout << "The decoded message is - " << message << "\n";
}
