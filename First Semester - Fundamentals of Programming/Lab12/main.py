from domain.validators import StudentValidator, DisciplinaValidator, NotaValidator
from services.studentservice import StudentService
from services.disciplinaservice import DisciplinaService
from services.noteservice import NotaService
from repository.studentfile import StudentFileRepository
from repository.disciplinafile import DisciplinaFileRepository
from repository.notefile import NoteFileRepository
from ui.console import Consola

"""
reps = StudentiInMemoryRepository()
repd = DisciplineInMemoryRepository()
repn = NoteInMemoryRepository()
"""

reps = StudentFileRepository('studenti.txt')
repd = DisciplinaFileRepository('discipline.txt')
repn = NoteFileRepository('note.txt')
vals = StudentValidator()
ctrs = StudentService(reps, vals)
vald = DisciplinaValidator()
ctrd = DisciplinaService(repd, vald)
valn = NotaValidator()
ctrn = NotaService(repn, valn)
ui = Consola(ctrs, ctrd, ctrn)

ui.afiseazaUI()

    
