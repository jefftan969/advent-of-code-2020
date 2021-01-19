#!/usr/bin/python3

# Extended Euclidean algorithm to compute Bezout coefficients (from Wikipedia)
def extended_gcd(a, b):
    (old_r, r) = (a, b)
    (old_s, s) = (1, 0)
    (old_t, t) = (0, 1)

    while r != 0:
        quotient = old_r // r
        (old_r, r) = (r, old_r - quotient * r)
        (old_s, s) = (s, old_s - quotient * s)
        (old_t, t) = (t, old_t - quotient * t)

    # Return Bezout coefficients
    return (old_s, old_t)

with open('day13.txt', 'r') as f:
    lines = f.readlines()
    start = int(lines[0])
    bus_strings = lines[1].split(',')
    buses = {int(bus_strings[i]):i for i in range(len(bus_strings)) if bus_strings[i] != 'x'}

    # Want to find x such that x === a mod n, by repeatedly using Chinese remainder theorem on pairs
    # Assumes that all bus numbers are pairwise coprime
    a = 0
    n = 1
    for (key, value) in buses.items():
        a_i = (-value) % key
        n_i = key

        # Compute Bezout coefficients, find solution, and update a and n (solution from Wikipedia)
        (m, m_i) = extended_gcd(n, n_i)
        x = a*m_i*n_i + a_i*m*n
        n = n*n_i
        a = x % n

    print(a)
