bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf,scanf,fscanf,fopen,fclose,fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fscanf msvcrt.dll  
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    fisierinput times 30 db 0
    format db "%s",0
    n dd 0
    formatn db "%d",0
    mod_acces db "r",0
    descriptor dd -1
    cuvant times 30 db 0
    vocale db "aeiou"
    contor db 0
    mod_acces2 db "a",0
    fisierout db "output.txt",0
    formatcuv db "%s ",0
    descriptor2 dd -1
; our code starts here
segment code use32 class=code
    start:
        push dword fisierinput
        push dword format
        call [scanf]
        add esp,4*2
        
        push dword n
        push dword formatn
        call [scanf]
        add esp,4*2
        
        push dword mod_acces
        push dword fisierinput
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        
        mov [descriptor],eax
    repeta:
    
        push dword cuvant
        push dword format
        push dword[descriptor]
        call [fscanf]
        add esp, 4*3
        
        cmp eax,1
        jne afara
        
        mov byte[contor],0
        mov esi,cuvant
    parcurg:
        lodsb
        cmp al,0
        je af
        mov ecx,6
        mov ebx,0
    vfvoc:
        mov dl,[vocale+ebx]
        cmp al,dl
        je p
        inc ebx
        loop vfvoc
        add byte[contor],1 
    p:
        jmp parcurg
    af:
        mov edx,0
        mov dl,[contor]
        cmp edx,[n]
        jne peste
        
        push dword mod_acces2
        push dword fisierout
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je eroare
        mov [descriptor2],eax
        
        push dword cuvant
        push dword formatcuv
        push dword [descriptor2]
        call [fprintf]
        add esp, 4*3
    
        push dword [descriptor2]
        call [fclose]
        add esp,4*1
    eroare: 
    
    peste:
        jmp repeta
        
    afara:    
        push dword[descriptor]
        call [fclose]
        add esp,4*1
    final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
