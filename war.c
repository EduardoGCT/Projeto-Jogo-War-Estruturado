#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// --- Constantes Globais ---
#define MAX_TERRITORIOS 5
#define MAX_STRING 50

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct {
    char nome[MAX_STRING];
    char cor[MAX_STRING];
    int tropas;
} territorio;

// --- Protótipos das Funções ---
void mostrar_territorios(territorio *mapa);
void cadastro_territorio(territorio *mapa);
void mapa_do_mundo(const territorio *mapa);
void atacar(territorio* atacante, territorio* defensor);
void limparBufferEntrada();
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes);
int verificarMissao(char* missao, territorio* mapa, int tamanho);


int main() {

    //definindo aleatoriedade no srand
    srand(time(NULL));

    //alocação dinâmica de memória com ponteiros
    territorio *mapa;
    
    mapa = (territorio *) calloc(MAX_TERRITORIOS, sizeof(territorio));

    //verificando se alocação deu certo
    if (mapa == NULL){
        printf("Erro: Falha ao alocar memoria.\n");
    }

    //chamando função cadastro para preencher os dados
    cadastro_territorio(mapa);

    //mostrando todos os territórios cadastrados
    mostrar_territorios(mapa);

    //Vetor de missoes
    const char* missoes[] = {
    "Conquistar 3 territorios",
    "Eliminar todas as tropas de um territorio",
    "Conquistar um territorio",
    "Ganhar 3 tropas",
    "Dominar todos os territorios"
    };
    int totalDeMissoes = 5;

    char destino[MAX_STRING]; //Guarda a missão do jogador

    // Chamada da função para atribuir missão
    atribuirMissao(destino, missoes, totalDeMissoes);

    //Inicializando o loop do jogo
    int opcao, atacante_id, defensor_id;
    
    do{
        mapa_do_mundo(mapa);

        

        printf("\n___ Sua missao neste jogo (Exercito %s): %s ___\n\n", mapa[0].cor, destino);

        //mostrando menu geral
        int opcao;
        printf("\n---MENU DE ACOES---\n");

        printf("1 - Atacar\n");
        printf("2 - Verificar missao\n");
        printf("0 - Sair\n");
        printf("Escolha sua acao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao){
            case 1: //Atacar
                printf("--- Fase de ataque ---\n");

                printf("Escolha o territorio atacante (1 a 5, ou 0 para sair): ");
                scanf("%d", &atacante_id);

                if(atacante_id == 0) break; //sai do loop

                printf("Escolha o territorio defensor (1 a 5): ");
                scanf("%d", &defensor_id);

                territorio *p_atq = &mapa[atacante_id - 1];
                territorio *p_def = &mapa[defensor_id - 1];

                limparBufferEntrada();
                atacar(p_atq, p_def);
                break;
            
            case 2: //verificar missão
                if (verificarMissao(destino, mapa, MAX_TERRITORIOS)) {
                    printf("\n==================================\n");
                    printf(" PARABENS! Voce cumpriu sua missao!\n");
                    printf("==================================\n");
                } else {
                    printf("\n___ Voce ainda nao cumpriu seu objetivo. Continue lutando! ___\n\n");
                } 
                break;

            case 0:
                atacante_id = 0; // Para encerrar o loop
            break;  
        }

    } while (atacante_id != 0);

    printf("Aperto Enter para continuar...");
    getchar();

    


    free(mapa);

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.


// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).
void cadastro_territorio (territorio *mapa){

    for(int i = 0; i < MAX_TERRITORIOS; i++){
    printf("===========================\n");
    printf("Cadastro de territorio %d\n", i + 1);
    

    printf("Nome do territorio: ");
    fgets(mapa[i].nome, MAX_STRING, stdin);
    mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

    printf("Cor do territorio: ");
    fgets(mapa[i].cor, MAX_STRING, stdin);
    mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

    printf("Numero de tropas: ");
    scanf("%d", &mapa[i].tropas);
    limparBufferEntrada();
    printf("===========================\n");

    }
}

/**
 * @brief Mostra na tela todos os territórios cadastrados
 * @param mapa array de territorios
 */
void mostrar_territorios(territorio *mapa){
    for (int i = 0; i < MAX_TERRITORIOS; i++){
        printf("-----------------------------\n");
        printf("TERRITORIO %d: \n", i + 1);
        printf("- Nome: %s\n", mapa[i].nome);
        printf("- cor: %s\n", mapa[i].cor);
        printf("- tropas: %d\n", mapa[i].tropas);
        printf("----------------------------\n");
    }
    printf("\n\n");
}

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
void mapa_do_mundo(const territorio *mapa){
    printf("--- MAPA DO MUNDO - ESTADO ATUAL ---\n");
    printf("===========================================\n\n");

    for (int i = 0; i < MAX_TERRITORIOS; i++){
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    printf("\n");
}

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.
void atacar(territorio* atacante, territorio* defensor){
    printf("\n\n--- Execucao do ataque ---\n");

    //verificando se o endereço é válido
    if (atacante == NULL || defensor == NULL) return;

    printf("\n%s atacando %s!", atacante->nome, defensor->nome);

    // 1. Gerando os dados (rand)
    int dado_ataque = (rand() % 6) + 1;
    int dado_defesa = (rand() % 6) + 1;

    printf("\nDado do Atacante: [%d]", dado_ataque);
    printf("\nDado do Defensor: [%d]\n", dado_defesa);

    // 2. Comparação e Manipulação de Memória via Ponteiros
    if (dado_ataque > dado_defesa) {
        printf("Vitoria do atacante! %s perdeu 1 tropa.\n", defensor->nome);
        defensor->tropas -= 1; // Altera o valor no endereço de memória do defensor

        if(defensor->tropas <= 0){
            strcpy(defensor->cor, atacante->cor);
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", defensor->nome, atacante->cor);
        }
    } 
    else {
        printf("O defensor resistiu! %s perdeu 1 tropa.\n", atacante->nome);
        atacante->tropas -= 1; // Altera o valor no endereço de memória do atacante
    }
    printf("-----------------------\n");

    printf("pressione Enter para continuar...");
    getchar();
}

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes){
    int indiceSorteado = rand() % totalMissoes;
    strcpy(destino, missoes[indiceSorteado]);
}

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.
/**
 * @brief Avalia se a missão do jogador foi cumprida.
 * @return Retorna 1 se venceu, 0 se ainda não cumpriu.
 */
int verificarMissao(char* missao, territorio* mapa, int tamanho) {
    // Caso 1: Dominar todos os territórios (todos devem ter a mesma cor)
    if (strcmp(missao, "Dominar todos os territorios") == 0) {
        for (int i = 1; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, mapa[0].cor) != 0) {
                return 0; // Se achar uma cor diferente da primeira, ainda não ganhou
            }
        }
        return 1;
    }

    // Caso 2: Ganhar 3 tropas (pelo menos um território com 3 ou mais tropas)
    if (strcmp(missao, "Ganhar 3 tropas") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas >= 3) return 1;
        }
    }

    // Caso 3: Conquistar 3 territorios (exemplo: ter 3 territórios com a mesma cor do primeiro)
    if (strcmp(missao, "Conquistar 3 territorios") == 0) {
        int contagem = 0;
        char* minhaCor = mapa[0].cor; // Assume que o primeiro território é o seu
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, minhaCor) == 0) contagem++;
        }
        return (contagem >= 3);
    }

    return 0; // Missão ainda não cumprida
}

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada(){
    int c;
    while ((c= getchar()) != '\n' && c != EOF);
}