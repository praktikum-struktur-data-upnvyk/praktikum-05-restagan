// =============================================================================
// student.cpp — Implementasi Mahasiswa
// Pertemuan 5: Stack (Tumpukan) dengan Linked List
// =============================================================================
// FILE YANG BOLEH DIEDIT      : src/student.cpp  ← HANYA FILE INI
// FILE YANG TIDAK BOLEH DIEDIT: src/student.h, tests/checker.cpp, tests/report.h
//
//
//         ============================================================
//                    STUDY CASE: APLIKASI EDITOR "TULIS"
//         ============================================================
//
// Pertemuan ini hanya punya SATU soal, yaitu study case di bawah ini. Empat
// pekerjaan yang Anda kerjakan nanti semuanya berasal dari cerita yang sama —
// tidak ada cerita baru lagi di bawah.
//
// -----------------------------------------------------------------------------
// LATAR
// -----------------------------------------------------------------------------
// Anda diminta membuat bagian dalam sebuah aplikasi editor teks bernama Tulis.
// Jendelanya sudah jadi, menunya sudah lengkap, tetapi dua fiturnya masih mati
// total: tombol Undo tidak melakukan apa-apa, dan pemeriksa kurung selalu
// menjawab "tidak tahu".
//
// Yang menarik, kedua fitur itu ternyata membutuhkan bentuk penyimpanan yang
// sama persis, dan itulah materi pertemuan ini: STACK.
//
// -----------------------------------------------------------------------------
// FITUR PERTAMA — TOMBOL UNDO
// -----------------------------------------------------------------------------
// Setiap kali Anda mengetik sesuatu, editor mencatat perubahan itu. Ketika Anda
// menekan Ctrl+Z, yang dibatalkan adalah perubahan yang PALING TERAKHIR Anda
// lakukan — bukan yang paling awal.
//
// Coba bayangkan kalau aturannya terbalik. Anda mengetik "halo", lalu menghapus
// satu huruf, lalu menebalkan sebuah kata. Menekan Ctrl+Z seharusnya
// mengembalikan penebalan tadi. Kalau yang dibatalkan justru pengetikan "halo"
// yang paling awal, tulisan Anda akan berantakan.
//
// Aturan "yang terakhir masuk, dialah yang pertama keluar" itu disebut LIFO —
// Last In, First Out. Bentuk penyimpanan yang mengikuti aturan itu disebut
// STACK, atau tumpukan.
//
// Namanya tumpukan karena persis seperti menumpuk piring: piring baru selalu
// diletakkan di ATAS, dan piring yang bisa diambil juga selalu yang paling
// ATAS. Tidak ada cara mengambil piring dari tengah tumpukan tanpa membongkar
// yang di atasnya.
//
//       top
//        |
//       [30]  <- paling terakhir masuk, paling pertama keluar
//        |
//       [20]
//        |
//       [10]  <- paling pertama masuk, paling terakhir keluar
//        |
//      nullptr
//
//   `top`      penunjuk ke elemen PALING ATAS. Bernilai `nullptr` berarti
//              tumpukannya sedang KOSONG.
//
//   `next`     penunjuk ke elemen DI BAWAHNYA. Elemen paling bawah `next`-nya
//              bernilai `nullptr`.
//
// Perhatikan: seluruh tumpukan hanya dikenali dari SATU penunjuk saja, yaitu
// `top`. Anda tidak pernah perlu tahu di mana dasarnya, karena semua operasi
// hanya terjadi di puncak.
//
// -----------------------------------------------------------------------------
// TIDAK ADA KAPASITAS
// -----------------------------------------------------------------------------
// Tumpukan ini dibangun dari linked list, jadi tidak ada batas banyaknya elemen
// dan tidak ada keadaan "penuh". Node dibuat dengan `new` saat data masuk, dan
// dilepas dengan `delete` saat data keluar. Sebanyak apa pun perubahan yang
// Anda ketik, seluruhnya harus tertampung.
//
// Yang tetap ada adalah keadaan KOSONG — dan itu keadaan yang sah, bukan
// kesalahan. Menekan Ctrl+Z pada dokumen yang baru dibuka memang seharusnya
// tidak melakukan apa-apa.
//
// -----------------------------------------------------------------------------
// FITUR KEDUA — PEMERIKSA KURUNG
// -----------------------------------------------------------------------------
// Tulis juga dipakai untuk menulis kode, jadi ia punya pemeriksa kurung: setiap
// `(`, `[`, dan `{` harus punya pasangan penutup yang sejenis, dan pasangannya
// tidak boleh bersilangan.
//
//     ( a + b ) * ( c - d )      seimbang
//     { [ ( ) ] }                seimbang, tiga jenis bersarang rapi
//     ( a + [ b ) ]              TIDAK — pasangannya bersilangan
//     ( a + b                    TIDAK — ada buka tanpa penutup
//     ) (                        TIDAK — penutup muncul lebih dulu
//
// Sekilas ini soal yang sama sekali berbeda. Tetapi coba perhatikan barisan
// `{ [ ( ) ] }`. Ketika Anda bertemu `)`, yang harus dipasangkan dengannya
// adalah `(` — yaitu tanda buka yang PALING TERAKHIR dibuka dan belum tertutup.
// Sesudah itu, ketika bertemu `]`, pasangannya `[` yang sekarang menjadi yang
// terakhir belum tertutup.
//
// Itu aturan LIFO yang sama persis. Jadi fitur kedua ini memakai tumpukan yang
// sama dengan fitur pertama — dan itulah sebabnya keduanya ada di satu study
// case.
//
// -----------------------------------------------------------------------------
// SATU SESI MENGETIK
// -----------------------------------------------------------------------------
// Berikut satu sesi pemakaian Tulis. EMPAT langkah bertanda SOAL adalah
// pekerjaan yang harus Anda kerjakan.
//
//   1. Anda mengetik. Setiap perubahan dicatat ke tumpukan riwayat, dan yang
//      baru selalu diletakkan di PUNCAK.
//                                                            -> SOAL 1
//
//   2. Status bar menampilkan perubahan terakhir tanpa membatalkannya, dan
//      panel riwayat menampilkan seluruh tumpukan dari atas ke bawah.
//      (Kedua fungsi untuk ini SUDAH DISEDIAKAN, namanya peek dan display.
//       Baca `peek` baik-baik — ia pembanding yang berguna untuk Soal 2.)
//
//   3. Anda menekan Ctrl+Z. Perubahan yang paling terakhir dibatalkan, dan
//      editor perlu tahu perubahan apa itu supaya bisa mengembalikannya.
//      Menekan Ctrl+Z pada dokumen yang belum diapa-apakan tidak boleh
//      membuat aplikasi berhenti tidak wajar.
//                                                            -> SOAL 2
//
//   4. Anda menekan Ctrl+S. Dokumen tersimpan, dan seluruh riwayat undo
//      dibuang sekaligus supaya tidak menumpuk di memori.
//                                                            -> SOAL 3
//
//   5. Anda beralih menulis kode. Editor memeriksa apakah tanda kurung yang
//      Anda ketik sudah berpasangan dengan seimbang.
//                                                            -> SOAL 4
//
// Keempat pekerjaan bertanda SOAL itulah seluruh isi pertemuan ini. Di bawah
// nanti Anda tidak akan menemukan cerita baru — yang ada hanya rincian teknis:
// apa yang diminta, arti parameternya, contohnya, dan hal yang ikut dinilai.
//
// -----------------------------------------------------------------------------
// DAFTAR PEKERJAAN DAN BOBOTNYA
// -----------------------------------------------------------------------------
//   Soal 1  push             perubahan dicatat ke puncak tumpukan     25 poin
//   Soal 2  pop              Ctrl+Z membatalkan yang paling terakhir  30 poin
//   Soal 3  clear            Ctrl+S membuang seluruh riwayat undo     20 poin
//   Soal 4  kurungSeimbang   pemeriksa kurung pada kode               25 poin
//
// -----------------------------------------------------------------------------
// SUDAH DISEDIAKAN, TIDAK DINILAI
// -----------------------------------------------------------------------------
//   inisialisasi   menyiapkan tumpukan baru menjadi kosong
//   isEmpty        apakah tumpukannya sedang kosong
//   peek           melihat puncak tanpa mengambilnya
//   display        membaca seluruh isi tumpukan menjadi satu baris teks
//
//   Keempatnya ada di bagian bawah file ini, sudah ditulis lengkap. Pakai
//   `display` sesering mungkin untuk memeriksa hasil kerja Anda sendiri.
//
// -----------------------------------------------------------------------------
// ATURAN YANG BERLAKU UNTUK SELURUH PEKERJAAN
// -----------------------------------------------------------------------------
//   - Nilai yang disimpan bertipe `int`. Boleh negatif, boleh nol, dan boleh
//     muncul lebih dari sekali.
//   - Tumpukan yang KOSONG adalah keadaan yang sah, bukan kesalahan.
//   - Tidak ada kapasitas dan tidak ada keadaan "penuh".
//   - Node dibuat dengan `new` dan yang keluar dilepas dengan `delete`.
//   - Tidak ada satu pun fungsi yang mencetak ke layar.
//   - Signature fungsi serta bentuk `struct Node` dan `struct Stack` adalah
//     kontrak; isi fungsi, nama variabel, dan struktur kode di dalamnya
//     sepenuhnya bebas.
//   - Anda boleh menambah fungsi bantu sendiri.
//   - Soal 1, 2, dan 3 dinilai sendiri-sendiri: checker menyiapkan tumpukan
//     ujinya tanpa memakai fungsi Anda.
//   - Soal 4 adalah PENERAPAN. Kalau Anda mengerjakannya memakai `push` dan
//     `pop` buatan Anda sendiri, pastikan kedua soal itu sudah benar lebih
//     dulu. Anda juga boleh mengerjakannya dengan cara lain — yang dinilai
//     hanya hasilnya.
//
// MENCOBA SENDIRI:
//   File ini adalah program C++ utuh. Tekan tombol Run di VS Code, atau:
//     g++ -std=c++17 src/student.cpp -o latihan && ./latihan
//   Yang dijalankan adalah main() di bagian paling bawah file ini. main() itu
//   memeragakan sesi mengetik tadi, tidak ikut dinilai, dan bebas Anda ubah.
//
// Sebelum diisi, compiler memunculkan peringatan "unused parameter".
// Itu wajar dan tidak mengurangi nilai.
// =============================================================================

#include "student.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// =============================================================================
// SOAL 1 — push                                                        25 poin
//          Langkah 1 pada cerita: perubahan dicatat ke puncak tumpukan
// =============================================================================
// Yang diminta:
//   Letakkan sebuah nilai baru di posisi PALING ATAS tumpukan. Seluruh nilai
//   yang sudah ada tetap tersimpan dengan urutan yang sama persis, hanya saja
//   sekarang mereka semua berada di bawah nilai baru itu.
//
// Parameternya:
//   `s`         stack milik pemanggil. Bertanda `&`, sehingga perubahan pada
//               `s.top` ikut terasa oleh pemanggil
//   `nilai`     nilai yang mau dimasukkan
//   kembalian   `true` bila nilai baru berhasil masuk
//
// Contoh:
//   Sebelum : Top -> 20 -> 10
//   Operasi : push(s, 30)
//   Sesudah : Top -> 30 -> 20 -> 10                (kembalian true)
//
//   Tumpukan yang tadinya kosong:
//   Sebelum : (kosong)
//   Operasi : push(s, 10)
//   Sesudah : Top -> 10                            (kembalian true)
//
// Yang perlu diingat:
//   - Sesudah pemanggilan, `s.top` harus menunjuk node yang baru.
//
//   - Node baru harus tersambung ke isi lama: `next` miliknya menunjuk elemen
//     yang tadinya berada di puncak. Lupa menyambung ini membuat seluruh isi
//     lama hilang dari tumpukan sekaligus bocor di memori.
//
//   - Pada tumpukan yang tadinya KOSONG, `next` milik node baru bernilai
//     `nullptr`. Perhatikan bahwa keadaan ini sebenarnya tidak perlu ditangani
//     secara khusus — kalau Anda menyambungkannya ke `s.top` yang memang sedang
//     bernilai `nullptr`, hasilnya sudah benar dengan sendirinya.
//
//   - Nilai-nilai lama tidak boleh hilang dan urutannya tidak boleh berubah.
//
//   - TIDAK pernah ada penolakan karena penuh. Stack berbasis linked list tidak
//     punya kapasitas tetap, jadi kembaliannya selalu `true` selama node
//     barunya berhasil dibuat. Ini beda pokok dengan stack berbasis array.
//
//   - Setiap pemanggilan menyediakan TEPAT SATU node baru.
// =============================================================================

bool push(Stack& s, int nilai) {
    return false;
}

// =============================================================================
// SOAL 2 — pop                                                         30 poin
//          Langkah 3 pada cerita: Ctrl+Z membatalkan yang paling terakhir
// =============================================================================
// Yang diminta:
//   Keluarkan elemen PALING ATAS dari tumpukan, beri tahu pemanggil nilainya,
//   lalu buang node-nya dari memori.
//
//   Perhatikan bahwa fungsi ini harus melaporkan DUA hal sekaligus: berhasil
//   atau tidak, dan nilai apa yang keluar. Karena satu fungsi hanya bisa
//   mengembalikan satu nilai, yang kedua disampaikan lewat parameter `nilai`
//   yang bertanda `&` — pemanggil menyediakan variabelnya, dan fungsi ini
//   mengisinya.
//
//   Bandingkan dengan `peek` yang SUDAH DISEDIAKAN di bagian bawah file ini.
//   Keduanya sama-sama mengisi `nilai` dan sama-sama mengembalikan `bool`.
//   Bedanya cuma satu: `peek` hanya melihat, sedangkan `pop` benar-benar
//   mengeluarkan dan membuang node-nya.
//
// Parameternya:
//   `s`         stack milik pemanggil. Bertanda `&`
//   `nilai`     tempat pemanggil menerima nilai yang keluar. Bertanda `&`
//   kembalian   `true` bila ada elemen yang benar-benar dikeluarkan, `false`
//               bila tumpukannya sedang kosong
//
// Contoh:
//   Sebelum : Top -> 30 -> 20 -> 10
//   Operasi : int n; pop(s, n);
//   Sesudah : Top -> 20 -> 10, n bernilai 30       (kembalian true)
//
//   Tumpukan kosong (underflow):
//   Sebelum : (kosong)
//   Operasi : int n = -999; pop(s, n);
//   Sesudah : (kosong), n TETAP bernilai -999      (kembalian false)
//
// Yang perlu diingat:
//   - Yang keluar selalu elemen PALING ATAS, yaitu yang paling terakhir masuk
//     di antara yang masih tersimpan.
//
//   - `nilai` harus sudah diisi SEBELUM node-nya di-`delete`. Node yang sudah
//     dilepas tidak boleh dibaca lagi — membacanya sesudah `delete` adalah
//     kesalahan yang hasilnya tidak dapat diramalkan.
//
//   - Sesudah pemanggilan yang berhasil, `s.top` berpindah ke elemen di
//     bawahnya, dan seluruh sisanya tetap tersimpan dengan urutan yang sama.
//
//   - Node yang keluar harus dibuang dengan `delete`, TEPAT SATU node per
//     pemanggilan yang berhasil.
//
//   - UNDERFLOW: bila tumpukannya sedang kosong, kembaliannya `false`, dan
//     `nilai` TIDAK BOLEH DISENTUH SAMA SEKALI. Ini ikut diuji: checker mengisi
//     variabel penerima dengan sebuah penanda lebih dulu, lalu memastikan
//     penanda itu masih utuh sesudah pemanggilan yang gagal.
//
//   - Mengeluarkan elemen terakhir membuat tumpukan menjadi kosong, dan
//     tumpukan itu harus tetap bisa dipakai lagi sesudahnya.
// =============================================================================

bool pop(Stack& s, int& nilai) {
    return false;
}

// =============================================================================
// SOAL 3 — clear                                                       20 poin
//          Langkah 4 pada cerita: Ctrl+S membuang seluruh riwayat undo
// =============================================================================
// Yang diminta:
//   Buang seluruh isi tumpukan sekaligus, sampai benar-benar kosong.
//
//   Perhatikan baik-baik kata "dibuang". Memutus sambungannya saja tidak cukup.
//   Anda memang bisa langsung membuat `s.top` bernilai `nullptr`, dan sekilas
//   tumpukannya akan terlihat kosong — tetapi seluruh node-nya masih menumpuk
//   di memori, dan sekarang tidak ada satu pun yang bisa mencapainya lagi
//   karena alamat puncaknya sudah hilang. Keadaan seperti itu disebut kebocoran
//   memori, dan itu ikut dinilai.
//
// Parameternya:
//   `s`         stack milik pemanggil. Bertanda `&`
//   kembalian   tidak ada (fungsi bertipe `void`)
//
// Contoh:
//   Sebelum : Top -> 50 -> 40 -> 30 -> 20 -> 10
//   Operasi : clear(s)
//   Sesudah : (kosong) — `s.top` bernilai nullptr, dan kelima node sudah
//             dibuang dari memori
//
// Yang perlu diingat:
//   - Sesudah selesai, `s.top` bernilai `nullptr`.
//
//   - SELURUH node harus dibuang dengan `delete`, bukan hanya yang paling atas.
//     Banyaknya node yang dibuang ikut dihitung checker secara TEPAT.
//
//   - Hati-hati: alamat node berikutnya harus sudah disimpan SEBELUM sebuah
//     node di-`delete`. Node yang sudah dilepas tidak boleh dibaca lagi,
//     termasuk untuk mencari node selanjutnya.
//
//   - Memanggilnya pada tumpukan yang SUDAH kosong adalah sah: tidak terjadi
//     apa-apa, dan program tidak boleh berhenti tidak wajar.
//
//   - Memanggilnya dua kali berturut-turut juga harus aman.
//
//   - Sesudah dikosongkan, tumpukan harus tetap bisa DIPAKAI LAGI seperti biasa.
//     Dokumen yang baru disimpan tetap bisa diketik lagi sesudahnya.
// =============================================================================

void clear(Stack& s) {
}

// =============================================================================
// SOAL 4 — kurungSeimbang                                              25 poin
//          Langkah 5 pada cerita: pemeriksa kurung pada kode
// =============================================================================
// Yang diminta:
//   Tentukan apakah tanda kurung di dalam sebuah teks sudah berpasangan dengan
//   seimbang. Ada tiga jenis yang diperiksa: `(` dengan `)`, `[` dengan `]`,
//   dan `{` dengan `}`.
//
//   Seimbang berarti tiga hal sekaligus:
//     - setiap tanda buka punya penutup yang SEJENIS;
//     - setiap tanda tutup punya pembuka yang SEJENIS; dan
//     - pasangan-pasangannya tidak saling BERSILANGAN.
//
//   Yang harus Anda putuskan sendiri: bagaimana mengingat tanda buka mana yang
//   masih menunggu pasangan. Petunjuknya sudah ada di bagian cerita — ketika
//   bertemu sebuah tanda tutup, yang harus dipasangkan dengannya selalu tanda
//   buka yang PALING TERAKHIR dibuka dan belum tertutup.
//
// Parameternya:
//   `ekspresi`  teks yang mau diperiksa. Boleh sepanjang apa pun, boleh juga
//               kosong
//   kembalian   `true` bila seimbang, `false` bila tidak
//
// Contoh:
//   "( a + b ) * ( c - d )"   -> true
//   "{[()]}"                  -> true    tiga jenis, bersarang rapi
//   ""                        -> true    tidak ada kurung sama sekali
//   "halo dunia"              -> true    karakter lain diabaikan
//   "( a + b ) * ( c - d"     -> false   ada buka tanpa penutup
//   "( a + [ b ) ]"           -> false   pasangannya bersilangan
//   ")("                      -> false   penutup muncul lebih dulu
//   "(]"                      -> false   penutupnya tidak sejenis
//
// Yang perlu diingat:
//   - Karakter selain keenam tanda kurung itu DIABAIKAN. Huruf, angka, spasi,
//     dan tanda baca lain tidak mempengaruhi hasil.
//
//   - Teks kosong bernilai seimbang, begitu juga teks yang sama sekali tidak
//     memuat tanda kurung.
//
//   - Tanda tutup yang muncul saat tidak ada satu pun tanda buka yang menunggu
//     berarti TIDAK seimbang. Contohnya `)(` — walaupun jumlah buka dan
//     tutupnya sama-sama satu.
//
//   - Menghitung jumlah saja TIDAK CUKUP. Perhatikan `( a + [ b ) ]`: jumlah
//     bukanya dua dan tutupnya dua, tetapi pasangannya bersilangan sehingga
//     tetap tidak seimbang. Yang menentukan adalah URUTANNYA.
//
//   - Di akhir pemeriksaan, tidak boleh ada tanda buka yang masih menunggu
//     pasangan.
//
//   - Tidak ada batas banyaknya tanda kurung yang boleh bersarang.
//
//   - Anda boleh memakai `push` dan `pop` buatan Anda sendiri, atau cara lain
//     yang menghasilkan perilaku sama. Yang dinilai hanya hasilnya. Bila Anda
//     memakai stack sendiri, jangan lupa membereskan node-nya sebelum fungsi
//     ini selesai.
// =============================================================================

bool kurungSeimbang(const string& ekspresi) {
    return false;
}

// =============================================================================
// SUDAH DISEDIAKAN — TIDAK DINILAI, TIDAK PERLU DIUBAH
// =============================================================================
// Keempat fungsi di bawah sudah ditulis lengkap.
//
// `peek` sengaja disediakan sebagai PEMBANDING untuk Soal 2. Perhatikan
// bentuknya baik-baik: `pop` yang Anda kerjakan punya kerangka yang sama
// persis, hanya saja ia juga memindahkan `s.top` dan membuang node-nya.
// =============================================================================

void inisialisasi(Stack& s) {
    s.top = nullptr;
}

bool isEmpty(const Stack& s) {
    return s.top == nullptr;
}

bool peek(Stack& s, int& nilai) {
    if (s.top == nullptr) return false;

    nilai = s.top->data;
    return true;
}

string display(Stack& s) {
    string hasil;
    for (Node* p = s.top; p != nullptr; p = p->next) {
        if (!hasil.empty()) hasil += " ";
        hasil += to_string(p->data);
    }
    return hasil;
}

// =============================================================================
// MAIN() — memeragakan sesi mengetik. TIDAK dinilai, bebas diubah.
// =============================================================================
// Di bawah ini file ini menjadi program C++ biasa. Tekan Run di VS Code, atau
// jalankan lewat terminal:
//
//     g++ -std=c++17 src/student.cpp -o latihan
//     ./latihan
//
// Isinya menjalankan sesi mengetik di Tulis secara berurutan, dan menampilkan
// hasil tiap langkah berdampingan dengan jawaban yang benar — sehingga Anda
// bisa langsung membandingkan.
//
// SARAN URUTAN PENGERJAAN: kerjakan Soal 1 lebih dulu, karena seluruh percobaan
// di bawah memerlukan tumpukan yang sudah terisi.
//
// SATU ATURAN YANG TIDAK BOLEH DILANGGAR
// --------------------------------------
// cin hanya boleh dipakai DI DALAM main() ini. JANGAN menaruh cin di dalam
// keempat fungsi yang dinilai. Saat menilai, checker memanggil fungsi-fungsi
// itu tanpa memberi masukan apa pun, jadi cin di sana akan membaca sampah — dan
// nilai Anda berubah-ubah setiap kali dinilai, dari kode yang sama persis.
//
// (Baris #ifndef di bawah hanya urusan teknis: saat menilai, checker memakai
//  main() miliknya sendiri, jadi main() Anda dilewati supaya tidak bentrok.)
// =============================================================================

#ifndef ADA_MAIN_LAIN

static const char* benarSalah(bool nilai) {
    return nilai ? "true" : "false";
}

static ostream& baris(const string& label) {
    return cout << "    " << left << setw(20) << label << ": ";
}

// Keadaan ringkas tumpukan, dibaca lewat fungsi yang sudah disediakan.
static void keadaan(Stack& s) {
    baris("display") << "\"" << display(s) << "\"\n";

    int atas = 0;
    if (peek(s, atas)) baris("puncak") << atas << "\n";
    else               baris("puncak") << "(tidak ada)\n";

    baris("isEmpty") << benarSalah(isEmpty(s)) << "\n";
}

// Satu percobaan Ctrl+Z, lengkap dengan nilai yang diterima.
static void cobaUndo(Stack& s) {
    int nilai = -999;
    bool berhasil = pop(s, nilai);
    baris("Ctrl+Z");
    if (berhasil) cout << "berhasil, yang dibatalkan = " << nilai << "\n";
    else          cout << "gagal (riwayat kosong), nilai tidak diubah ("
                       << nilai << ")\n";
}

static void langkah(const string& teks) {
    cout << "\n" << teks << "\n";
}

int main() {
    cout << "==================================================\n";
    cout << " Study Case — Aplikasi Editor \"Tulis\"\n";
    cout << " Memeragakan satu sesi mengetik\n";
    cout << " (bagian ini tidak ikut dinilai)\n";
    cout << "==================================================\n";

    Stack s;
    inisialisasi(s);

    langkah("[0] Dokumen baru dibuka, riwayat undo masih kosong");
    keadaan(s);

    langkah("[1] SOAL 1 — push: tiga perubahan diketik (10, 20, lalu 30)");
    baris("push 10") << benarSalah(push(s, 10)) << "\n";
    baris("push 20") << benarSalah(push(s, 20)) << "\n";
    baris("push 30") << benarSalah(push(s, 30)) << "\n";
    keadaan(s);
    cout << "\n    Yang benar: display \"30 20 10\", puncak 30, isEmpty false\n";

    langkah("[2] SOAL 1 — tidak ada batas kapasitas: 10 perubahan sekaligus");
    bool semuaMasuk = true;
    for (int i = 1; i <= 10; ++i) {
        if (!push(s, i * 100)) semuaMasuk = false;
    }
    baris("semua masuk") << benarSalah(semuaMasuk) << "\n";
    keadaan(s);
    cout << "\n    Yang benar: semua masuk true — linked list tidak pernah penuh\n";

    langkah("[3] SOAL 2 — pop: Ctrl+Z, yang dibatalkan harus 1000");
    cobaUndo(s);
    keadaan(s);
    cout << "\n    Yang benar: berhasil dengan nilai 1000\n";

    langkah("[4] SOAL 3 — clear: Ctrl+S, seluruh riwayat undo dibuang");
    clear(s);
    keadaan(s);
    cout << "\n    Yang benar: display \"\", puncak (tidak ada), isEmpty true\n";

    langkah("[5] SOAL 2 — Ctrl+Z pada dokumen yang baru disimpan (underflow)");
    cobaUndo(s);
    cout << "\n    Yang benar: gagal, dan nilainya tetap -999 (tidak disentuh)\n";

    langkah("[6] Tumpukan tetap bisa dipakai lagi sesudah dikosongkan");
    push(s, 7);
    push(s, 8);
    keadaan(s);
    cout << "\n    Yang benar: display \"8 7\"\n";

    langkah("[7] SOAL 4 — kurungSeimbang: pemeriksa kurung pada kode");
    const string contoh[] = {
        "( a + b ) * ( c - d )",   // seimbang
        "{[()]}",                  // seimbang, tiga jenis bersarang
        "",                        // seimbang, tidak ada kurung
        "( a + b ) * ( c - d",     // kurang tutup
        "( a + [ b ) ]",           // bersilangan
        ")("                       // tutup muncul lebih dulu
    };
    for (int i = 0; i < 6; ++i) {
        cout << "    \"" << contoh[i] << "\"";
        for (size_t j = contoh[i].size(); j < 24; ++j) cout << " ";
        cout << " -> " << benarSalah(kurungSeimbang(contoh[i])) << "\n";
    }
    cout << "\n    Yang benar: true, true, true, false, false, false\n";

    // -------------------------------------------------------------------------
    // Mau mencoba dengan teks yang Anda ketik sendiri? Hapus tanda // di bawah
    // ini, lalu jalankan lagi.
    // -------------------------------------------------------------------------
    // cout << "\nKetik satu ekspresi: ";
    // string punyaAnda;
    // getline(cin, punyaAnda);
    // cout << "seimbang? " << benarSalah(kurungSeimbang(punyaAnda)) << endl;

    clear(s);

    cout << "\n==================================================\n";
    cout << " Sesi selesai. Silakan ubah bagian ini untuk\n";
    cout << " mencoba percobaan Anda sendiri.\n";
    cout << "==================================================\n";

    return 0;
}
#endif
