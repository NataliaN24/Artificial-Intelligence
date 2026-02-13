python -m venv .venv 

 Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
 
 .venv\Scripts\Activate.ps1
 
pip install fmi-ai-judge

judge run --bench frog-leap.exe
judge run --bench flp.exe


judge run --bench npuzzle.exe
judge run --bench np.exe

judge run --bench n-queens.exe
judge run --bench nq.exe

judge run --bench tsp.exe
judge run --bench kp.exe

python.exe -m pip install --upgrade pip
judge run --bench tictactoe.exe
judge run --bench ttt.exe
