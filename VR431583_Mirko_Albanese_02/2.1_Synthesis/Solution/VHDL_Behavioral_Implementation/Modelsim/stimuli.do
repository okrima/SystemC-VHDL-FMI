echo "Apertura file stimuli.do"

# fai ripartire la simulazione (se non lo fai, 
# continua dal punto nel quale si era fermato)

vsim work.xtea

restart -f 

# tolgo e ri-aggiungo i segnali del modulo alla schermata
add wave *

# RESET DEL MODULO
# il clock parte con 0, resta basso 1ns, viene alzato, 
# resta alto 1ns, e ripeto il processo ogni 2ns
force clock 0 0 ns, 1 1 ns -r 2ns
force reset 1 0 ns, 0 2 ns
run 5ns

# CONFIGURAZIONE _ 1 Input keys
force in1 16#6a1d78c8
force in2 16#8c86d67f
force input_ready 1
run 2 ns
force input_ready 0
run 4 ns

# CONFIGURAZIONE _ 2 Input keys
force in1 16#2a65bfbe
force in2 16#b4bd6e46
force input_ready 1 
run 2 ns
force input_ready 0
run 4 ns

# CRIPTAZIONE
force in1 16#12345678 0 ns
force in2 16#9abcdeff 0 ns
force command 0    
force input_ready 1   
run 4 ns
force input_ready 0   
run 264 ns

# il clock parte con 0, resta basso 1ns, viene alzato, 
# resta alto 1ns, e ripeto il processo ogni 2ns
#force clock 0 0 ns, 1 1 ns -r 2ns
#force reset 1 0 ns, 0 2 ns
#run 5ns

# CONFIGURAZIONE _ 1 Input keys
force in1 16#6a1d78c8
force in2 16#8c86d67f
force input_ready 1
run 2 ns
force input_ready 0
run 4 ns

# CONFIGURAZIONE _ 2 Input keys
force in1 16#2a65bfbe
force in2 16#b4bd6e46
force input_ready 1 
run 2 ns
force input_ready 0
run 4 ns

# DECRIPTAZIONE
force in1 16#99bbb92b 0 ns
force in2 16#3ebd1644 0 ns
force command 1   
force input_ready 1   
run 4 ns
force input_ready 0   
run 300 ns
