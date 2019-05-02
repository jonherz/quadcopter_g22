io(1) = linio('open_loop/Thrust converter',1,'input')
io(3) = linio('open_loop/PS -> S 2',1,'openoutput')
io(4) = linio('open_loop/PS -> S 3',1,'openoutput')
io(5) = linio('open_loop/PS -> S 4',1,'openoutput')
io(6) = linio('open_loop/PS -> S 5',1,'openoutput')
%options = linearizeOptions('SampleTime',0.01);
op = operpoint('open_loop')
sys = linearize('open_loop',io,op);%,options)