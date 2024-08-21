#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <omp.h>
#include <time.h>
#include <string.h>
#include <fstream>

clock_t tInicio, tFim, tDecorrido;
using std::cout; using std::string; using std::endl;
using std::ofstream;

string lerArquivo(const string& caminho) {
    struct stat sb{};
    string resultado;

    FILE* arquivo = fopen(caminho.c_str(), "r");
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return "";
    }

    stat(caminho.c_str(), &sb);
    resultado.resize(sb.st_size);
    fread(const_cast<char*>(resultado.data()), sb.st_size, 1, arquivo);
    fclose(arquivo);

    return resultado;
}

void salvarArquivo(const string& caminho, const char* conteudo) {
    ofstream arquivoSaida(caminho);
    if (!arquivoSaida) {
        cout << "Erro ao criar o arquivo!" << endl;
        return;
    }
    arquivoSaida << conteudo;
    arquivoSaida.close();
}

int main() {
    string nomeDoArquivo("arquivos/DNA.txt");
    string conteudo = lerArquivo(nomeDoArquivo);
    
    if (conteudo.empty()) {
        return -1; 
    }
    
    char fita[conteudo.length() + 1];
    strcpy(fita, conteudo.c_str());

    tInicio = clock();
    for (int i = 0; i < conteudo.length(); i++) {		
        switch (toupper(fita[i])) {
            case 'A':
                fita[i] = 'T';
                break;
            case 'C':
                fita[i] = 'G';
                break;
            case 'T':
                fita[i] = 'A';
                break;
            case 'G':
                fita[i] = 'C';
                break;
        }
    }
    tFim = clock();

    tDecorrido = ((tFim - tInicio) * 1000 / CLOCKS_PER_SEC); 
    printf("Tempo decorrido: %ld ms\n", tDecorrido);

    string nomeDoArquivoSaida("arquivos/DNA_transcrito.txt");
    salvarArquivo(nomeDoArquivoSaida, fita);

    return 0;
}
