data = load('data.txt');
inputs = data(:,1);
times = data(:,2);

figure;
plot(inputs, times, 'o-', 'LineWidth', 2);
xlabel('Tamaño de entrada (n)');
ylabel('Tiempo de ejecución (µs)');
// Si la variable "notation" existe, se actualiza el título
if exist('notation','var')
    title(['Análisis de Complejidad ' notation]);
else
    title('Análisis de Complejidad Big-O');
end
grid on;
