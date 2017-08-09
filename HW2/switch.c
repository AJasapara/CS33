// Name: Arpit Jasapara, UID: 504742401

long switch_prob (long x, long n)
{
	long result = x;
	switch(n) {
		case 60:
		case 62:
			result = x * 8;
			break;
		case 63:
			result = result >> 3;
			break;
		case 64:
			result = result << 4;
			result -= x;
			x = result;
		case 65:
			x *= x;
		case 61:
		default:
			result = x + 75;
	}
	return result;
}