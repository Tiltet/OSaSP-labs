<h1>Лабораторная работа №1</h1>

<h2>Введение</h2>
<p>Программа dirwalk, сканирующая файловую систему и выводящая
информацию в соответствии с опциями программы.</p>

<h2>Компиляция</h2>
<p>Для компиляции программы выполните следующие команды:</p>
<pre>
<code>https://github.com/Tiltet/OSaSP-labs.git</code>
<code>cd laba01</code>
<code>gcc -o dirwalk dirwalk.c</code>
<code>./dirwalk -ldfs /path/to/directory/for/scan</code>
</pre>

<h2>Режимы работы</h2>

<p>Программа <code>dirwalk</code> поддерживает два режима работы, управляемых через опцию <code>mode</code> при компиляции.</p>
<ol>
    <li><strong>Режим отладки (<code>mode=debug</code>):</strong></li>
    <pre><code>make mode=debug</code></pre>
    <li>Режим выпуска (<code>mode=release</code>):</strong></li>
    <pre><code>make mode=release</code></pre>
</ol>
<ul>
    <li>Для обработки опций использована библиотека <code>getopt_long()</code>.</li>
    <li>Программа поддерживает опции <code>-l</code>, <code>-d</code>, <code>-f</code>, <code>-s</code>.</li>
    <p>Допустимые опции:</p>
<ul>
    <li><code>-l</code>: только символические ссылки.</li>
    <li><code>-d</code>: только каталоги.</li>
    <li><code>-f</code>: только файлы.</li>
    <li><code>-s</code>: сортировать вывод в соответствии с <code>LC_COLLATE</code>.</li>
</ul>
<p style="color:orange">Если опции не указаны, выводятся каталоги, файлы и символические ссылки.</p>

___

<h1>Лабораторная работа №2</h1>

<h2>Введение</h2>
<p>Программы parent и сhild, сканирующая файловую систему и выводящая
информацию в соответствии с опциями программы.</p>

<h2>Компиляция</h2>
<p>Для компиляции программы выполните следующие команды:</p>
<pre>
<code>git clone https://github.com/Tiltet/OSaSP-labs.git</code>
<code>cd laba02</code>
<code>gcc -o parent parent.c</code>
<code>gcc -o child child.c</code>
<code>export CHILD_PATH=./child</code>
<code>./parent env.txt</code>
</pre>

<h2>Описание работы</h2>

<ul>
<li>Создается переменная окружения <code>CHILD_PATH</code> перед запуском <code>parent</code>,
содержащая путь к директории <code>child</code>.</li>
<li>Процесс <code>parent</code>:</li>
    <ul>
        <li>Получает и печатает отсортированные переменные окружения.</li>
        <li>Цикл ввода с клавиатуры:</li>
        <ul>
            <li><code>+</code>: Создает дочерний процесс с помощью <code>fork/execve</code>, запускает <code>child</code>.
                Имя: <code>child_XX (00-99)</code>.</li>
            <li><code>*</code>: То же самое, но получает путь к <code>child</code> из аргументов командной строки <code>main</code></li>
            <li><code>&</code>: То же самое, но получает путь к <code>child</code> из переменных окружения.</li>
            <li><code>q</code>: Завершает работу.</li>
            <li>Запускает дочерний процесс с уменьшенным набором переменных окружения из файла.</li>
        </ul>
    </ul>
<li>Процесс <code>child</code>:</li>
    <ul>
        <li>Печатает имя, PID, PPID.</li>
        <li>Открывает файл с переменными окружения, печатает значения.</li>
        <li>Завершает работу.</li>
    </ul>
</ul>

___

<h1>Лабораторная работа №3</h1>
<h2>#TODO</h2>




