    from domain.validators import StudentValidator, DisciplinaValidator, NotaValidator
from services.studentservice import StudentService
from services.disciplinaservice import DisciplinaService
from services.noteservice import NotaService
from repository.studentfile import StudentFileRepository
from repository.disciplinafile import DisciplinaFileRepository
from repository.notefile import NoteFileRepository
from repository.studentrepo import StudentiInMemoryRepository
from repository.disciplinarepo import DisciplineInMemoryRepository
from repository.noterepo import NoteInMemoryRepository
from ui.console import Consola

"""
reps = StudentiInMemoryRepository()
repd = DisciplineInMemoryRepository()
repn = NoteInMemoryRepository()
"""

reps = StudentFileRepository('C:\\Users\\user\\PycharmProjects\\pythonProject\\studenti.txt')
repd = DisciplinaFileRepository('C:\\Users\\user\\PycharmProjects\\pythonProject\\discipline.txt')
repn = NoteFileRepository('C:\\Users\\user\\PycharmProjects\\pythonProject\\note.txt')
vals = StudentValidator()
ctrs = StudentService(reps, vals)
vald = DisciplinaValidator()
ctrd = DisciplinaService(repd, vald)
valn = NotaValidator()
ctrn = NotaService(repn, valn)
ui = Consola(ctrs, ctrd, ctrn)

ui.afiseazaUI()

    
