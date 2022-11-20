<h1> <b> Tugas-Besar-IF2110-K2-A </b> </h1>

## Penjelasan Singkat mengenai Program 
<p> Mesin BNMO adalah suatu mesin berbasis CLI (command-line interface) yang dibuat dengan menggunakan bahasa C dan memanfaatkan Struktur Data (Abstract Data Type) untuk memudahkan pemrograman. Mesin BNMO merupakan mesin dimana mesin itu dapat menjalankan suatu proses yang berhubungan dengan pengolahan makanan. Tugas mesin BNMO ini secara umum adalah mengolah suatu bahan menjadi makanan. Namun, tidak hanya itu masih ada fungsi lainnya.  

Mesin BNMO ini dapat dimanfaatkan untuk membuat suatu makanan. Mesin ini diprogram untuk bisa memasak namun tidak hanya itu, membeli suatu bahan, mixing, merebus, memotong, menampilkan makanan yang ada serta menunjukan kadaluarsa suatu makanan. Mesin dapat bergerak dalam suatu peta yang di dalam peta itu terdapat daerah dimana mesin dapat melakukan suatu aksi terhadap makanan.  </p>

<h2> Langkah Penggunaan Program </h2>

1. Clone terlebih dahulu repository ini
> $ git clone https://github.com/rizkyrsyd28/Tugas-Besar-IF2110-K2-A.git

2. Pindah ke directory dimana file main disimpan
>$ cd Tugas-Besar-IF2110-K2-A\src\Main

3. <i> Compile </i> file main.c
>$ gcc main.c -o (nama)

4. Run file tersebut pada terminal. Silakan coba salah satu dari opsi dibawah ini.
>$ (nama)

>$ ./(nama)

</br>
<h2> Anggota Kelompok </h2>
<ol> 
<li> Rizky Abdillah Rasyid - 13521109
<li> Shelma Salsabila - 13521115
<li> Juan Christopher Santoso - 13521116
<li> Ahmad Ghulam Ilham - 13521118
<li> Raynard Tanadi - 13521143
<li> Muhammad Zaki Amanullah - 13521146
</ol>
</br>

<h2> List Folder </h2>
<ul>
<li> ADT
<p> Berisikan semua file yang berisikan untuk deklarasi dan implementasi dari ADT yang dibutuhkan. Setiap Folder ADT mengandung setidaknya 3 file, file header (.h), file implementasi program (.c), dan file driver.</p>
    <ul>
    <li> ADT Point
    <li> ADT Time
    <li> ADT Makanan
    <li> ADT Simulator
    <li> ADT List Statik
    <li> ADT Matrix
    <li> ADT Queue
    <li> ADT Stack
    <li> ADT Mesin Kata
    <li> ADT Tree
    <li> ADT String
    <li> ADT Kulkas
    </ul>
<li> Main
<p> Berisikan semua file yang berisikan code untuk menjalankan program utama. Terdiri atas beberapa file utama yaitu: </p>
<ul>
<li> main
<p> Berisikan algoritma utama dalam menjalankan program </p>
<li> submain
<p> Berisikan algoritma dan fungsi-fungsi penunjang main </p>
<li> parser
<p> Berisikan algoritma untuk membaca konfigurasi file.txt </p>
<li> driver
<p> Bukan bagian dari pelaksanaan program, hanya digunakan untuk melakukan test sebelum sebuah algoritma diimplementasikan dalam main </p>
</ul>

<li> TextFile
<p> Berisikan semua file txt yang dijadikan konfigurasi awal dari berjalannya program. </p>
</ul>

## Daftar Fitur dan Status Pengerjaan 
| Fitur  | Status Pengerjaan | 
| ------------- | ------------- |
| Insiasi dan Terminasi  | DONE  |
| Simulator  | DONE  |
| Makanan dan Konfigurasi | DONE  |
| Resep dan Konfigurasi | DONE  |
| Peta dan Konfigurasi | DONE  |
| Inventory | DONE  |
| Buy dan Delivery List | DONE  |
| Pengolahan Makanan | DONE  |
| Wait  | DONE  |
| Undo / Redo  | DONE  |
| Catalog  | DONE  |
| Cookbook  | DONE  |
| Notifikasi | DONE  |
| Bonus 1 (Kulkas) | DONE  |
| Bonus 2 (Waktu Pengolahan Makanan) | DONE  |
| Bonus 3 (Rekomendasi Makanan) |       |
| Bonus 4 (AUTO BNMO) |       |

## Pembagian Tugas Pada Source Code
| Nama | NIM | Tugas  |
|-----| ----| ------|
| Rizky Abdillah Rasyid | 13521109| ADT Point, ADT Priority Queue, ADT N-ary Tree, ADT Resep, Pembacaan konfigurasi peta, Pembacaan konfigurasi resep, Command Move, Command Pengolahan Makanan (Mix, Chop, Fry, dan Boil), Command Cookbook |
| Shelma Salsabila | 13521115 | ADT Time, ADT Matriks, Commad Catalog, ASCII  ART |
| Juan Christopher Santoso | 13521116 | Pembacaan Konfigurasi Makanan, ADT Makanan, ADT Mesin Kata dan Mesin Karakter, ADT String, Bonus 1 (Kulkas), Bonus 2 (Pengolahan Makanan), Mekanisme Pengaturan Masuk, Keluar, dan Waktu pada Delivery List, Process List, dan Inventory pada Main, Command Help, Error Handling pada User Input, Pembuatan README |
| Ahmad Ghulam Ilham | 13521118 | Penulisan Notifikasi pada Main, Command Buy|
| Raynard Tanadi | 13521143 | ADT Stack, ADT Simulator, Command Undo, Redo |
| Muhammad Zaki Amanullah | 13521146 | ADT List Statik, Command Inventory, Command Wait |

## Pembagian Tugas Pada Laporan
| Nama | NIM | Tugas  |
|-----| ----| ------|
| Rizky Abdillah Rasyid | 13521109| Struktur data ADT point, Struktur data ADT Prioqueue, Struktur data ADT N-ary Tree, Struktur data ADT Resep  |
| Shelma Salsabila | 13521115 | Struktur data ADT Time, Struktur data ADT Matrix, Ringkasan Laporan, Lampiran (Form Asistensi, Notulensi, dan Log Activity) |
| Juan Christopher Santoso | 13521116 | Penjelasan Tambahan Spesifikasi Tugas (Bonus 1 dan 2), Struktur Data ADT Makanan, Struktur Data ADT Mesin Kata dan Mesin Kata, Struktur Data ADT String, Data Test Start, Konfigurasi, dan Main Menu, Data Test Catalog, Data Test Cookbook, Data Test Inventory, Data Test Delivery, Data Test Process, Data Test Fridge|
| Ahmad Ghulam Ilham | 13521118 | Data Test Move, Data Test Buy, Data Test Wait |
| Raynard Tanadi | 13521143 | Struktur Data ADT Simulator, Struktur Data ADT Stack, Data Test Undo dan Redo, Test Script Undo dan Redo |
| Muhammad Zaki Amanullah | 13521146 | Struktur Data ADT List Statik, Test Script Inventory, Test Script Fridge Put, Test Script Fridge Show, Test Script Fridge Take |



<h2> Quotes sejenak :</h2>
<h2> <b> Tubes itu keharusan, Tipes itu kepastian </b> </h2>

![alt_text](https://res.cloudinary.com/practicaldev/image/fetch/s--Tfu5ipMH--/c_imagga_scale,f_auto,fl_progressive,h_900,q_auto,w_1600/https://dev-to-uploads.s3.amazonaws.com/uploads/articles/raakfuz5mupt3q5oog8n.jpeg)

