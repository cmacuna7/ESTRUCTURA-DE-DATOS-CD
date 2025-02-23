function graph_big_o_matlab(notation)
    data = load('data.txt');
    inputs = data(:,1);
    times = data(:,2);

    figure;
    plot(inputs, times, 'o-', 'LineWidth', 2);
    xlabel('Tamaño de entrada (n)');
    ylabel('Tiempo de ejecución (µs)');
    title(['Análisis de Complejidad ' notation]);
    grid on;
end