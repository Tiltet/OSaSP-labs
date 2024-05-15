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

<h1>Лабораторная работа No 3</h1>

<h2>Введение</h2>
<p>Программа, управляющая дочерними процессами и упорядочивающая вывод в stdout от них, используя сиг-
налы SIGUSR1 (для запрета вывода информации) и SIGUSR2 (для разрешения вывода информации).</p>

<h2>Компиляция</h2>
<p>Для компиляции программы выполните следующие команды:</p>
<pre>
<code>git clone https://github.com/Tiltet/OSaSP-labs.git</code>
<code>cd OSaSP-labs/lab3</code>
<code>make</code>
</pre>
    Программа поддерживает опции <code>+</code>, <code>-</code>, <code>l</code>, <code>k</code>,
      <code>s</code>, <code>g</code>, <code>s&lt;num&gt;</code>, <code>g&lt;num&gt;</code>, <code>p&lt;num&gt;</code>, <code>q</code>.</li>
      <ul>
    <li><code>-</code> : Уничтожить последний созданный дочерний процесс</li>
    <li><code>q</code> : Удалить все процессы и выйти</li>
    <li><code>l</code> : Вывести информацию о всех дочерних процессах</li>
    <li><code>k</code> : Завершить все дочерние процессы</li>
    <li><code>s</code> : Запретить статистику для всех дочерних процессов</li>
    <li><code>g</code> : Разрешить статистику для всех дочерних процессов</li>
    <li><code>s&lt;num&gt;</code> : Остановить статистику для дочернего процесса &lt;num&gt;</li>
    <li><code>g&lt;num&gt;</code> : Разрешить статистику для дочернего процесса &lt;num&gt;</li>
    <li><code>p&lt;num&gt;</code> : Остановить все и запросить информацию от дочернего процесса &lt;num&gt;</li>
</ul>


---

<h1>Лабораторная работа No 4</h1>

<h2>Условие задания</h2>

<p>Основной процесс создает очередь сообщений и ожидает нажатия клавиш, порождая и завершая процессы двух типов — производителей и потребителей. Очередь сообщений представляет собой кольцевой буфер, содержащий указатели на сообщения, счетчики добавленных и извлеченных сообщений.</p>

<h3>Формат сообщений</h3>

<ul>
    <li><strong>type</strong> (1 байт) - тип сообщения.</li>
    <li><strong>hash</strong> (2 байта) - контрольные данные.</li>
    <li><strong>size</strong> (1 байт) - длина данных в байтах (от 0 до 256).</li>
    <li><strong>data</strong> - данные сообщения, выровненные до ближайшего кратного четырём размера.</li>
</ul>

<h3>Генерация сообщений</h3>

<p>Производители генерируют сообщения, используя системный генератор <code>rand(3)</code>, чтобы определить размер (<code>size</code>) и данные (<code>data</code>). Размер сообщения (<code>size</code>) вычисляется как остаток от деления на 257. Если остаток равен 256, размер сообщения устанавливается в 0, что приводит к длине сообщения в 256 байт.</p>

<p>Контрольные данные (<code>hash</code>) формируются из всех байтов сообщения.</p>

<h3>Семафоры и мьютексы</h3>

<p>Для синхронизации доступа к очереди используются два семафора (<code>emptySpaceCount</code> и <code>filledSpaceCount</code>) и мьютекс (или одноместный семафор).</p>

<h3>Действия производителей и потребителей</h3>

<ul>
    <li><strong>Производители</strong> формируют и добавляют сообщения в очередь, увеличивая счетчик добавленных сообщений после каждой операции.</li>
    <li><strong>Потребители</strong> извлекают сообщения из очереди, проверяют контрольные данные и увеличивают счетчик извлеченных сообщений.</li>
</ul>

<h3>Завершение работы процессов</h3>

<p>Процессы должны завершить свою работу при получении сигнала о завершении, завершая текущую операцию перед выходом.</p>

<h3>Дополнительные требования</h3>

<ul>
    <li>Предусмотреть задержки для обеспечения возможности просмотра вывода в процессе выполнения программы.</li>
    <li>Обеспечить защиту от тупиковых ситуаций, возникающих из-за отсутствия производителей или потребителей.</li>
    <li>Предусмотреть возможность просмотра текущего состояния очереди и процессов при помощи нажатия определенной клавиши.</li>
</ul>

<h2>Запуск и компиляция через Makefile</h2>

<p>Для компиляции программы используйте следующие команды:</p>

<pre><code>make all  # Компиляция всех исходных файлов
./program  # Запуск программы
make clean  # Очистка скомпилированных объектных файлов и исполняемого файла
</code></pre>




