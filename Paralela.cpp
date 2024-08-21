#include <iostream>
#include <omp.h>
#include <time.h>
#include <string.h>
#include <fstream>

clock_t tInicio, tFim, tDecorrido;
using std::cout; using std::string; using std::endl;
using std::ofstream;

string lerArquivo(const string& caminho) {
    string resultado;

    FILE* arquivo = fopen(caminho.c_str(), "r");
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return "";
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    resultado.resize(tamanho);
    fread(&resultado[0], 1, tamanho, arquivo);
    fclose(arquivo);

    return resultado;
}

void salvarArquivo(const string& caminho, const string& conteudo) {
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

    char* fita = new char[conteudo.length() + 1];
    strcpy(fita, conteudo.c_str());

    tInicio = clock();
    omp_set_num_threads(2); // Define o número de threads para 2
    #pragma omp parallel for 
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

    delete[] fita;

    return 0;
}
