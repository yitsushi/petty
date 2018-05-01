# PeTTY

```
make dev    # with DEBUG_LEVEL - log error, info and debug
make        # with ERROR_LEVEL - log only error
```


### lldb note for self

```
❯ lldb ./bin/petty
(lldb) target create "./bin/petty"
Current executable set to './bin/petty' (x86_64).
(lldb) break set --file petty.c --line 34
Breakpoint 1: where = petty`select_pet_menu + 60 at petty.c:34, address = 0x000000010000139c
(lldb) break list
Current breakpoints:
1: file = 'petty.c', line = 34, exact_match = 0, locations = 1
  1.1: where = petty`select_pet_menu + 60 at petty.c:34, address = petty[0x000000010000139c], unresolved, hit count = 0

(lldb) break command add 1.1
Enter your debugger command(s).  Type 'DONE' to end.
> expr -- for (int i = 0; i < pet_count; i++) { printf("0x%llx - %s\n", pet_list[i], pet_list[i]); }
> DONE
```
