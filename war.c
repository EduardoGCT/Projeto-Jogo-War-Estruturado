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

//função para cadastrar territórios

// Funções de setup e gerenciamento de memória:

// Funções de interface com o usuário:
void mostrar_territorios(territorio *mapa);
void cadastro_territorio(territorio *mapa);
void mapa_do_mundo(const territorio *mapa);

// Funções de lógica principal do jogo:
void atacar(territorio* atacante, territorio* defensor);

// Função utilitária:
void limparBufferEntrada();

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
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
    
    int opcao, atacante_id, defensor_id;
    
    do{
        mapa_do_mundo(mapa);

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


        


    } while (atacante_id != 0);

    printf("Aperto Enter para continuar...");
    getchar();

    
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

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

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada(){
    int c;
    while ((c= getchar()) != '\n' && c != EOF);
}