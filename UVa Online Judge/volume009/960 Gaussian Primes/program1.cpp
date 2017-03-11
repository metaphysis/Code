if (a != 0 && b != 0)
{
    if (isPrime(a * a + b * b)) cout << "P\n";
    else cout << "C\n";
}
else
{
    int sum = abs(a) + abs(b);
    if (isPrime(sum) && sum % 4 == 3) cout << "P\n";
    else cout << "C\n";
}

continue;
