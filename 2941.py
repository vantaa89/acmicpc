st = input()
combined = ["dz=", "c=", "c-", "d-", "lj", "nj", "s=", "z="]

for ch in combined:
    while True:
        f = st.find(ch)
        if f == -1:
            break
        st = st[:f] + "0" + st[f+len(ch):]
        
print(len(st))

