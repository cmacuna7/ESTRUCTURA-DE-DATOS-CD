function graph_big_o(big_o)

    % Configurar valores según la notación
    switch big_o
        case 'O(1)'
            n = 1:10;
            y = ones(size(n));
            titulo = 'O(1) - Tiempo constante';
        case 'O(log n)'
            n = 2:20;
            y = log(n);
            titulo = 'O(log n) - Tiempo logarítmico';
        case 'O(n)'
            n = 1:100;
            y = n;
            titulo = 'O(n) - Tiempo lineal';
        case 'O(n log n)'
            n = 2:100;
            y = n .* log(n);
            titulo = 'O(n log n) - Tiempo linealítmico';
        case 'O(n^2)'
            n = 1:50;
            y = n.^2;
            titulo = 'O(n^2) - Tiempo cuadrático';
        case 'O(2^n)'
            n = 1:15;
            y = 2.^n;
            titulo = 'O(2^n) - Tiempo exponencial';
        case 'O(n!)'
            n = 1:10;
            y = arrayfun(@factorial, n);
            titulo = 'O(n!) - Tiempo factorial';
        otherwise
            error('Notación no soportada');
    end
    
    % Crear la gráfica
    figure;
    plot(n, y, 'LineWidth', 2);
    xlabel('Tamaño de entrada (n)');
    ylabel('Operaciones');
    title(titulo);
    grid on;

     waitfor(gcf);
end