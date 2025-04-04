;15. 6*3
mov [b],6 ;b=6
mov [a],3 ;a=3
mov al,[a] ;al=a
mov bl,[b] ;bl=b
mul bl ;ax=al*bl=6*3

;15. a-b-d+2+c+(10-b)       a,b,c,d-byte
mov al,[a] ;al=a
sub al,[b] ;al=al-b=a-b
sub al,[d] ;al=al-d=a-b-d
add al,2 ;al=al+2=a-b-d+2
add al,[c] ;al=al+c=a-b-d+2+c
mov bl,10 ;bl=10
sub bl,[b] ;bl=bl-b=10-b
add al,bl ;al=al+bl=a-b-d+2+c+(10-b)

;15. (a-b+c)-(d+d)     a,b,c,d-word
mov ax,[a] ;ax=a
sub ax,[b] ;ax=ax-b=a-b
add ax,[c] ;ax=ax+c=a-b+c
mov bx,[d] ;bx=d
add bx,[d] ;bx=bx+d=d+d
sub ax,bx ;ax=ax-bx=(a-b+c)-(d+d)

;15. (a*2)+2*(b-3)-d-2*c      a,b,c-byte   d-word
mov al,2 ;al=2
mul byte[a] ;ax=al*a=2*a
mov bx,ax ;bx=ax=2*a
mov ah,[b] ;ah=b    
sub ah,3 ;ah=ah-3=b-3
mov al,2 ;al=2
mul ah ;ax=al*ah=2*(b-3)
add bx,ax ;bx=bx+ax=(2*a)+2*(b-3)
sub bx,[d] ;bx=bx-d=(2*a)+2*(b-3)-d
mov al,2 ;al=2
mul byte[c] ;ax=al*c=2*c
sub bx,ax ;bx=bx-ax=(2*a)+2*(b-3)-d-2*c

;15. f*(e-2)/[3*(d-5)]      d-byte  e,f-word
mov al,3 ;al=3
mov dl,[d] ;dl=d
sub dl,5 ;dl=dl-5=d-5
mul dl ;ax=al*dl=3*(d-5)
mov bx,ax ;bx=ax=3*(d-5)
mov ax,[f] ;ax=f
mov cx,[e] ;cx=e
sub cx,2 ;cx=cx-2=e-2
mul cx ;dx:ax=ax*cx=f*(e-2)
div bx ;ax=dx:ax/bx=f*(e-2)/3*(d-5)


;Exerciții în plus
;25.64*4
mov al,64 ;al=64
mov bl,4 ;bl=4
mul bl ;ax=al*bl=64*4=256


;29.14/6
mov ax,14 ;ax=14
mov bl,6 ;bl=6
div bl ;al=ax/bl ah=ax%bl

;a,b,c,d-byte
;29.(b+c)+(a+b-d)
mov al,[b] ;al=b
add al,[c] ;al=al+c=b+c
mov bl,[a] ;bl=a
add bl,[b] ;bl=bl+b=a+b
sub bl,[d] ;bl=bl-d=a+b-d
add al,bl ;al=al+bl=(b+c)+(a+b-d)

;30.d-(a+b)-(c+c)
mov al,[d] ;al=d
mov bl,[a] ;bl=a
add bl,[b] ;bl=bl+b=a+b
sub al,bl ;al=al-bl=d-(a+b)
mov cl,[c] ;cl=c
add cl,[c] ;cl=cl+c=c+c
sub al,cl ;al=al-cl=d-(a+b)-(c+c)

;a,b,c,d-word
;28.(d-c)+(b+b-c-a)+d
mov ax,[d] ;ax=d
sub ax,[c] ;ax=ax-c=d-c
mov cx,[b] ;cx=b
add cx,[b] ;cx=cx+b=b+b
sub cx,[c] ;cx=cx-c=b+b-c
sub cx,[a] ;cx=cx-a=b+b-c-a
add ax,cx ;ax=ax+cx=(d-c)+(b+b-c-a)
add ax,[d] ;ax=ax+d=(d-c)+(b+b-c-a)+d

;30.a-b+(c-d+a)
mov ax,[a] ;ax=a
sub ax,[b] ;ax=ax-b=a-b
mov bx,[c] ;bx=c
sub bx,d ;bx=bx-d=c-d
add bx,a ;bx=bx+a=c-d+a
add ax,bx ;ax=ax+bx=a-b+(c-d+a)
 
;a,b,c-byte   d-word
;27.d/[(a+b)-(c+c)]
mov ax,[d] ;ax=d
mov bx,[a] ;bx=a
add bx,[b] ;bx=bx+b=a+b
mov cx,[c] ;cx=c
add cx,[c] ;cx=c+c
sub bx,cx ;bx=bx-cx=(a+b)-(c+c)
div bx ;al=ax/bx ah=ax%bx

;28.d+10*a-b*c
mov bx,[d] ;bx=d
mov al,10 ;al=10
mul byte[a] ;ax=al*a=10*a
add bx,ax ;bx=bx+ax=d+10*a
mov al,[b] ;al=b
mul byte[c] ;ax=al*c=b*c
sub bx,ax ;bx=bx-ax=d+10*a-b*c

;a,b,c,d-byte  e,f,g,h-word
;20.[(a+b+c)*2]*3/g
mov eax,[a] ;eax=a
add eax,[b] ;eax=eax+b=a+b
add eax,[c] ;eax=eax+c=a+b+c
mov ebx,6 ;ebx=2
mul ebx ;eax:edx=eax*ebx=[(a+b+c)*2]*3
mov ebx,[g] ;ebx=g
div ebx ;eax=eax:edx/ebx=[(a+b+c)*2]*3/g  edx=[(a+b+c)*2]*3%g 

;23.[(a+b)*2]/(a+d)
mov ax,[a] ;ax=a
add ax,[b] ;ax=a+b
mov bx,2 ;bx=2
mul bx ;dx:ax=ax*bx=(a+b)*2
mov cx,[a] ;cx=a
add cx,[d] ;cx=cx+d
div cx ;eax=dx:ax/cx  edx=dx:ax%cx
