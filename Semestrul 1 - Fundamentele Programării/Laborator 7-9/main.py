from domain.validators import StudentValidator, DisciplinaValidator, NotaValidator
from services.studentservice import StudentService
from services.disciplinaservice import DisciplinaService
from services.noteservice import NotaService
from repository.studentrepo import StudentiInMemoryRepository
from repository.disciplinarepo import DisciplineInMemoryRepository
from repository.noterepo import NoteInMemoryRepository
from ui.console import Consola

reps = StudentiInMemoryRepository()
vals = StudentValidator()
ctrs = StudentService(reps, vals)
repd = DisciplineInMemoryRepository()
vald = DisciplinaValidator()
ctrd = DisciplinaService(repd, vald)
repn = NoteInMemoryRepository()
valn = NotaValidator()
ctrn = NotaService(repn, valn)
ui = Consola(ctrs, ctrd, ctrn)

ui.afiseazaUI()
