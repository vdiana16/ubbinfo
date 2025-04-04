from ui.console import run
from ui.meniubatch import meniu_batch_mode
from ui.testare import teste_functionalitati
teste_functionalitati()
print("Ce fel de meniu preferati?")
print("   1 pentru meniu normal")
print("   2 pentru meniu batch mode")
j=input().strip()
if j == '1':
    run()
elif j == '2':
    meniu_batch_mode()
