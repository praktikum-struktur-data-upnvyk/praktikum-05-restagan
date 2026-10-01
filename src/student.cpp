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
bool push(Stack& s, int nilai) {
    Node* newNode = new Node;
    newNode->data = nilai;
    newNode->next = s.top;    
    s.top = newNode;    
    return true;
}

// =============================================================================
// SOAL 2 — pop                                                         30 poin
//          Langkah 3 pada cerita: Ctrl+Z membatalkan yang paling terakhir
// =============================================================================
bool pop(Stack& s, int& nilai) {
    if (s.top == nullptr) {
        return false;
    }
    
    Node* nodeHapus = s.top;
    nilai = nodeHapus->data; 
    s.top = s.top->next;
    delete nodeHapus;  
    return true;
}

// =============================================================================
// SOAL 3 — clear                                                       20 poin
//          Langkah 4 pada cerita: Ctrl+S membuang seluruh riwayat undo
// =============================================================================
void clear(Stack& s) {
    while (s.top != nullptr) {
        Node* nodeHapus = s.top;
        s.top = s.top->next;
        delete nodeHapus;
    }
}

// =============================================================================
// SOAL 4 — kurungSeimbang                                              25 poin
//          Langkah 5 pada cerita: pemeriksa kurung pada kode
// =============================================================================
bool kurungSeimbang(const string& ekspresi) {
    Stack s;
    s.top = nullptr;
    
    for (char c : ekspresi) {
        if (c == '(' || c == '{' || c == '[') {
            push(s, c);
        }
        else if (c == ')' || c == '}' || c == ']') {
            int nilaiPuncak;
            
            if (!pop(s, nilaiPuncak)) {
                clear(s);
                return false;
            }
            
            char kurungBuka = (char)nilaiPuncak;
            
            if ((c == ')' && kurungBuka != '(') ||
                (c == '}' && kurungBuka != '{') ||
                (c == ']' && kurungBuka != '[')) {
                clear(s);
                return false;
            }
        }
    }
    
    bool hasil = (s.top == nullptr);
    
    clear(s);
    return hasil;
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
