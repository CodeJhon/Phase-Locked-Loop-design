a = 1;
s = serialport("COM6",115200);
cont = 1;
limite_muestras = 20;
x = zeros(1,limite_muestras);

factor=1;

%Límites de visualización gráfica
ymax = 11;

while a==1
    %Leer y procesar
    idn = readline(s);
    vector_datos3 = str2num(idn);
    
    plot(vector_datos3,'r-');drawnow
    %xlim([1 limite_muestras]);
    %ylim([0 ymax]);drawnow

end
