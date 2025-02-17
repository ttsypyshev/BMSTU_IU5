-- Создание хранимой процедуры "retake" с параметрами m и n
CREATE PROCEDURE retake (m INT, n VARCHAR(255))
LANGUAGE SQL
AS $$
    -- Обновление значения в столбце "Оценка_2" для студентов с указанной группой
    UPDATE Студенты SET Оценка_2 = m WHERE Группа = n;
$$;

-- Вызов процедуры "retake" с передачей аргументов
CALL retake(5, '18У137');

-- Вывод всех данных из таблицы "Студенты"
SELECT * FROM Студенты;
