### UIT.Shuriken
 
if __name__ == "__main__":
    a, b, c, n = map(int, input().split(' '))
 
    ### Tong tat ca: n ^ 3
    ### 3 canh chong nhau: n
    ### 2 trong 3 canh chong nhau: 3 * n * (n - 1)
    ### 3 canh tao ra tam giac khong qua tam dong ho: 3 * n * ((n - 1) / 2) * ((n - 1) / 2 - 1)
    ans = n * n * n - n - 3 * n * (n - 1) - 3 * n * ((n - 1) // 2) * ((n - 1) // 2 - 1)
 
    ### Neu 3 canh bang nhau: chia cho 6
    ### Con khong, neu 2 trong ba canh bang nhau: chia cho 2
    if a == b and b == c:
        ans //= 6
    elif a == b or b == c or c == a:
        ans //= 2
 
    ### Mod 2^64
    ans %= (1 << 64)
 
    print(str(ans))
