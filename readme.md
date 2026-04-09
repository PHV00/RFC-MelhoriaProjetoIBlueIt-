**Engenharia de Software – Católica SC**

---

# Identificação

- **Título do Projeto:**  
  Melhorias no projeto I Blue It.

- **Linha de Projeto (Direction):**  
  IA / IoT / Dados

- **Autor:**  
  Pedro Henrique Vitoreti

- **Data da Proposta:**  
  12/04/2026

- **Versão:**  
  1.0

---

# 1. Visão do Produto e Impacto (O Problema)
  
Este projeto tem como fim identificar e melhorar o já consolidade jogo sério I Blue It, um software desenvolvido pela Universidade do Estado de Santa Catarina (UDESC) com o fim de auxiliar na fisioterapia de pacientes com problemas respiratorios, isso por meio da gamificação dos seus exercícios e análises dos resultados.Assim o projeto pretende análisar o software e aplicar as melhorias que forem encontradas, tanto tecnicas, como de demandas da comunidade que já utiliza o software.    

---

## 1.1 Contexto e Problema

A reabilitação respiratória é um processo terapêutico onde pacientes com disfunções respiratórias, usam de  uma abordagem sistemática, repetitiva e de longo prazo, o que pode reduzir a adesão do paciente ao tratamento.Nesse contexto os jogos sérios surgem como uma alternativa há tornar os exercícios mais motivadores, lúdicos e engajadores aos pacientes.

Nesse âmbito o software já desenvolvido pela inciativa de pesquisa da Udesc, I Blue It gamifica o tratamento e retorna dados uteis ao proficional da saúde que aplica o tratamento sobre paciente.O jogo consiste em um jogo de plataforma onde o usuario por meio de sua respiração em um equipamento IOT chamado PITACO no qual os valores obtidos são transformados em movimentos verticais inspirar sobe expirar desce assim fazendo o personagem controlado  "Blue" (o golfinho) desviar dos obstaculos ou capturar, além de possuir outros minigames com mesmo conceitos para exercicitar o paciente.Assim a solução atual já contempla calibração, histórico do jogador, armazenamento de dados e customização de parâmetros por profissionais.

<img width="675" height="318" alt="image" src="https://github.com/user-attachments/assets/27040498-d538-4f3c-86c5-6c2aa9d87c31" />

<img width="676" height="350" alt="image" src="https://github.com/user-attachments/assets/560cfbed-2ad8-4cab-9aac-4f24ad650252" />

link auxiliar com dados sobre software: https://udescmove2learn.wordpress.com/2018/04/26/i-blue-it/

Entretanto a iniativa percebeu lacunas no estado atual do software sendo estás ás:
- Dificuldade em ajustar a dificuldade dos exercicios ao estado atual do tratamento paciente (no modelo atual isso é configurado pelo profissional da saude oque pode acabar acaretando em erros).
- Necessidade de ampliar a captura de dados dos pacientes na hora do exercicios (adicionar um novo modulo para o biossensor de saturação periférica de oxigênio (SpO2)), com a finalidade de capturar mais dados sobre o paciente).
- Necessidade de ampliar os dados mostrados no dashboard do paciente ( adicionar os dados obtidos pela adição do modulo (SpO2) para o dashboard do paciente).
---

## 1.2 Origem da Demanda e Evidências

O software foi concebido em uma iniciativa do (LARVA)LAboratory for Research on Visual Applications da UDESC em colaboração com profissionais da aréa de fisioterapia respiratória e áreas correlatas, com o objetivo de atender a problematicas reais do dominio clinico.Sendo assim desde o principio o sistema tem como foco atender as necessidade de ferramentas que auxiem no processo de atendimento medico e tratamento de pacientes com problemas respiratorios.

O programa que foi concebido em 2018 já está atualmente na sua versão 5.0 e como tal já possue alguma experimentação por parte dos profissionais de saude, que o avaliaram possitivamente desde sua primeira versão, como pode-se ver nas avaliações de feitas já em 2018, onde os profissionais que tiveram contato com a ferramenta a avaliaram com nota de 4.1 de 5, demonstrando grande satisfação por parte dos envolvidos, já nos estagios iniciais do software. [referencia 2018 - Santos - I Blue It Um Jogo Sério para auxiliar na Reabilitação Respiratória.pdf]

Nesse contexto, tendo em mente o fim de ajudar ainda mais as equipes medicas no tratamento de doenças respiratorias, atrávez do aprimoramento das funcionalidades do software, que este projeto se origina, se propondo a aprimorar o software nas lacunas identificadas pela comunidade, com o fim de fornecer ao final uma ferramenta mais completa aos profissionais de saude.


## 1.3 Análise de Soluções Existentes (Benchmark)

**BubbleBreather**
Uma pequena coleção de jogos/atividades para exercícios respiratórios focados apenas há recuperação de pneumonia.Pode ser acessado pelo GitHub público e possui uma demo web ativa, por mais que não haja updates desde 2020. Possui um escopo mais estreito sendo jogos feito no propio browser, depende de microfone, com foco em exercícios específicos e não apresenta uma camada clínica robusta, comparável a dashboard terapêutico ou equipamentos IOT terapeuticos multimodalidade com sensores dedicados.

<img width="1915" height="947" alt="image" src="https://github.com/user-attachments/assets/45f80ec5-01ce-4d98-9ae2-b7e611d33471" />

link do repositorio : https://github.com/hcilab/BubbleBreather?tab=readme-ov-file

público-alvo : pessoas em recuperação de pneumonia

**PlayPhysio**

Uma inicitiva originada pela demanda de um pai cuja a filha possui fibrose cística e necessitava reralizar fisiotaripia, porém o tratamento não era engajador oque dificultava a participação e o interresse da criança.Com isso em mente, decidiu-se criar uma plataforma gamificada para que sua filha pudesse realizar seus exercicios de maneira mais ludica.Para fazer isso a plataforma acopla um equipamento IOT chamado PhysioPal ao equipamento terapeutico que ao se conectar via bluetooth no aparelho celular, registrara a pontuação no app.Não parece apresentar publicamente um ecossistema clínico tão robusto quanto o I Blue It, contendo dashboard terapêutico ou equipamentos IOT com sensores dedicados acoplados diretamente ao sistema, porém contem feedback em tempo real, e forneciemtno detalhado de dados.

<img width="1922" height="952" alt="image" src="https://github.com/user-attachments/assets/0c27559d-9700-4069-ac29-197f41ecb948" />

links do projeto:
- https://www.jbs.cam.ac.uk/ventures/playphysio/
- https://play.physio/

público-alvo : pessoas com problemas respiratorios(com foco em crianças)

**ACPlus Respiratory Assessment + OmniFlow**

A empresa Accelerated Care Plus produz duas soluções no ramo de terapia respiratoria sendo eles o ACPlus Respiratory Assessment uma solução voltado a ajudando a etapa de diagnóstico e decisão clinica de disfunções pulmonares, onde por meio de um dispositivo que captura os dados da respiração do paciente e os transmite a um Ipad por meio do bluetooth, que por sua vez retorna em formato de já de pronturario com a documentação clinica necessaria ao profissionais da saude.A outra chamado OmniFlow, tem como foco o tramatemnto gamificado atraves de tarapias pulmonares por meio de experiências interativas/gamificadas, onde o paciente realiza o tratamento atrávez de um dispositivo espirômetro bluetooth que capta seus dados, que são utilizados tanto nos exercicios, quanto posteriormente permite a analise por um profissional de saúde.Entre suas limitações podemos destacar a esclusividade de implantação, pois atualmente os sitemas são voltados as regulamentações e normativas do seu pais de origem Estados Unidos, oque limita a sua atuação preferencialmente apenas ao mercado estadunidense.

- OmniFlow
- <img width="1187" height="768" alt="image" src="https://github.com/user-attachments/assets/eef6fc3f-ce31-4bc5-8d05-24394b690f87" />

links dos produtos:
- https://acplus.com/acplus-respiratory-assessment-lp/
- https://acplus.com/technology/omniflow/
- https://acplus.com/blog/success-stories/omniflow-in-action-restoring-speech-confidence-and-connection/
  
público-alvo : pessoas com problemas respiratorios de modo amplo

---

### Comparação

| Solução | Pontos Fortes | Limitações |
|---|---|---|
| BubbleBreather |Permite a utilização do sistema em diversos ambientes(por ser em browser)|Não possue modulo clinico especializado|
| PlayPhysio |Permite tramamento gamificado, com expecialização em exercicios ludicos com foco infanto juvenil| Ecosistema clinico mais simplificado|
| OmniFlow |Permite o tratamento gamificado, e dados clinicos detalhados|Especificidade ao sistema ao ambiente estadunidense|

---

### Diferencial do Projeto

A análisando os concorentes elencados, podemos concluir que no campo das soluções respiratórias gamificadas elencadas se distribuem em três grandes grupos. O primeiro é o de soluções leves e acessíveis, como o BubbleBreather, que prioriza  a simplicidade tecnológica e acesso rápido. O segundo é o das soluções orientadas ao engajamento familiar e à adesão de maneira ludica, como o PlayPhysio. O terceiro é o das soluções com maior maturidade clínica e comercial, como o ACPlus Respiratory Assessment e o OmniFlow, fortemente ligado a atuação completa desda analise de desempenho do paciente em resposta ao tratamento, até ao tratamento gamificado e ludico.

Porém podemos perceber que enquanto os dois primeiros concorentes apresentem pontos fortes especificos e distintos, e que não cobrem todo o escopo já tratado pelo software I blue it, o terceiro apresenta uma solução completa e semelhante ao software I blue it, porém trazendo com isso uma diferença crucial, a especifidade ao ambiente estadunidense, oque impossibilita sua implementação de maneira simplificada em outros ambientes.

Dado isto percebemos a lacuna nitida de uma ferramenta completa ao ambiente fisioterapico brasileiro, que abranja de maneira relevante tanto a gamificação dos exercicios fisioterapicos, como a analise dos dados de desempenho do paciente, que é justamente a lacuna que o I blue it cobre.  

---

## 1.4 Público-Alvo

O sistema terá dois públicos principais:

Paciente em reabilitação respiratória: crianças e adultos que realizam exercícios terapêuticos respiratórios com acompanhamento profissional.

Profissional de saúde: fisioterapeutas respiratórios, fisioterapeutas clínicos, pneumologistas e demais especialistas que acompanham a sessão dos pacientes, definem parâmetros terapêuticos e analisam os resultados.

---

## 1.5 Objetivos do Projeto

### Objetivo Geral

Qual transformação o projeto pretende gerar.

---

### Objetivos Específicos

Liste **3 a 5 objetivos técnicos ou de produto**.

Exemplo:

- automatizar um processo manual
- permitir análise de dados
- criar um sistema de recomendação

---

## 1.6 Métricas de Sucesso (KPIs)

Como saberemos que o projeto foi bem sucedido?

Exemplos:

- latência inferior a 200ms
- acurácia da IA superior a 85%
- suporte a 100 usuários simultâneos
- redução do tempo de um processo em 30%

---

# 2. Engenharia de Requisitos

Esta seção define **o que o sistema fará**.

Evite descrições vagas.

---

## 2.1 Personas

Crie **1 a 3 personas principais**.

Inclua:

- nome fictício
- contexto
- objetivos
- principais dificuldades

Adicionar **imagens ou ilustrações** pode ajudar na compreensão.

---

## 2.2 Casos de Uso Principais

Liste os principais fluxos do sistema.

Exemplo:

- criar conta
- registrar dados
- consultar informações
- gerar relatórios

Sempre que possível inclua **diagramas de caso de uso**.

---

## 2.3 Requisitos Funcionais (RF)

Use a estrutura:

> O sistema deve permitir que **[ator] realize [ação]**.

Exemplo:

RF01 — O sistema deve permitir que o usuário crie uma conta.

RF02 — O sistema deve permitir que o usuário registre informações.

RF03 — O sistema deve permitir que o usuário visualize dados registrados.

---

## 2.4 Requisitos Não Funcionais (RNF)

Inclua requisitos relacionados a:

- desempenho
- segurança
- disponibilidade
- escalabilidade
- usabilidade

Exemplo:

RNF01 — O sistema deve suportar 100 usuários simultâneos.  
RNF02 — O tempo de resposta deve ser inferior a 300ms.  
RNF03 — O sistema deve utilizar autenticação segura.

---

## 2.5 Regras de Negócio

Exemplos:

- apenas usuários autenticados podem acessar determinados recursos
- determinadas operações exigem validação adicional

---

## 2.6 Fora do Escopo

Liste explicitamente **o que o sistema não fará**.

Isso ajuda a evitar crescimento descontrolado do projeto.

---

# 3. Fluxos e Comportamento do Sistema

Esta seção demonstra **como o sistema funciona**.

Use diagramas sempre que possível.

---

## 3.1 Fluxo Principal do Usuário

Apresente o fluxo principal do sistema.

Utilize:

- fluxogramas
- diagramas de atividades
- diagramas de sequência

Inclua **imagens dos diagramas**.

---

## 3.2 Fluxos Alternativos

Descreva cenários como:

- erros
- cancelamentos
- exceções

---

# 4. Mockups e Experiência do Usuário (UX)

Esta seção apresenta **a visualização inicial do produto antes da implementação**.

Mockups ajudam a validar:

- fluxo de navegação
- organização da interface
- interações do usuário
- clareza da experiência

Ferramentas sugeridas:

- Figma
- Excalidraw
- Balsamiq
- Whimsical
- protótipos desenhados à mão

---

## 4.1 Fluxo de Navegação

Apresente um diagrama mostrando como o usuário navega entre telas.

Exemplo:

Login → Dashboard → Cadastro → Relatório

Inclua **imagem do fluxo de navegação**.

---

## 4.2 Wireframes ou Mockups das Telas

Apresente os principais mockups do sistema.

Inclua pelo menos:

- tela inicial
- fluxo principal
- tela de entrada de dados
- tela de resultado ou visualização

Para cada tela inclua:

- imagem
- breve descrição da funcionalidade
- ações principais do usuário

Sempre que possível:

- inclua **links para protótipo navegável**
- inclua **prints das telas**

---

## 4.3 Fluxo de Interação do Usuário

Demonstre passo a passo um fluxo importante.

Exemplo:

1. usuário acessa o sistema  
2. cria conta  
3. registra dados  
4. visualiza resultados  

Inclua **sequência de telas ou fluxo visual**.

---

## 4.4 Feedback Inicial de Usuários (Opcional)

Se possível, inclua:

- comentários de usuários
- sugestões de melhoria
- validação inicial do mockup

---

# 5. Arquitetura do Sistema

Esta seção demonstra **como o sistema será construído**.

---

## 5.1 Diagrama C4

Apresente três níveis.
## 1. Nível 1: Diagrama de Contexto
É a **visão macro** do sistema. O foco aqui não é a tecnologia, mas sim como o software se encaixa no ecossistema e no mundo real.

* **Objetivo:** Mostrar o sistema como uma "caixa preta" e suas interações básicas com o ambiente externo.
* **O que incluir:**
    * **Atores:** Diferentes perfis de usuários (Ex: Cliente, Administrador, Operador).
    * **Sistemas Externos:** Softwares legados, serviços de terceiros ou provedores de identidade.
    * **Fluxo de Valor:** Como a informação entra, circula e sai do sistema principal.

---

## 2. Nível 2: Diagrama de Containers
Neste estágio, damos o primeiro **"zoom"**. Decompomos o sistema em suas unidades de execução independentes (containers).

* **Objetivo:** Apresentar a arquitetura de alto nível e as decisões tecnológicas fundamentais.
* **O que incluir:**
    * **Aplicações Web/Mobile:** Interfaces de usuário (Ex: SPA em React, App Android/iOS).
    * **Serviços de Backend:** Unidades lógicas de processamento (Ex: API Gateway, Microserviços em Node.js ou Go).
    * **Armazenamento:** Persistência de dados (Ex: PostgreSQL, MongoDB, Redis).
    * **Protocolos:** Como os containers se comunicam (Ex: JSON/HTTPS, gRPC, RabbitMQ).

---

## 3. Nível 3: Diagrama de Componentes
O foco agora é o que acontece **dentro de um único container** (como uma API específica ou um serviço de backend).

* **Objetivo:** Identificar as responsabilidades internas, padrões de código e a organização lógica.
* **O que incluir:**
    * **Estrutura Interna:** Organização das camadas (Ex: Controladores, Serviços, Repositórios e Clientes de API).
    * **Lógica de Negócio:** Componentes que encapsulam as regras específicas do domínio.
    * **Interações:** Como os componentes internos se orquestram para processar e responder a uma requisição.
---

## 5.2 Modelo de Dados

Apresente:

- DER (diagrama entidade relacionamento)
- esquema relacional
- modelo de documentos (NoSQL)

Inclua **diagramas do modelo de dados**.

---

## 5.3 Principais Componentes

Descreva os principais módulos do sistema.

Exemplo:

- API
- sistema de autenticação
- módulo de processamento
- camada de persistência

---

## 5.4 Stack Tecnológica

Liste as tecnologias utilizadas.

Para cada tecnologia explique **por que ela foi escolhida**.

Exemplo:

Node.js  
Escolhido pela capacidade de lidar com alto volume de requisições I/O.

---

# 6. Segurança e Privacidade

Inclua preocupações básicas de segurança.

Exemplos:

- proteção contra OWASP Top 10
- autenticação e autorização
- criptografia de dados sensíveis

---

## 6.1 Privacidade e LGPD

Explique:

- quais dados serão coletados
- como serão armazenados
- como o usuário poderá solicitar remoção de dados

---

# 7. Planejamento do Projeto

Defina os principais marcos de desenvolvimento.

| Marco | Descrição | Prazo |
|---|---|---|
| M1 | Setup do ambiente e prova de conceito | Semana X |
| M2 | MVP funcional | Semana Y |
| M3 | Testes e melhorias | Semana Z |

---

# 8. Referências

Inclua:

- artigos
- documentação técnica
- ferramentas utilizadas
- repositórios

---

# 9. Apêndices

Podem incluir:

- mockups adicionais
- resultados de pesquisa
- entrevistas com usuários
- diagramas complementares
- links para protótipos ou repositórios

Sempre que possível inclua **imagens, protótipos ou referências visuais**.

---

# 10. Parecer do Comitê de Avaliação

(A ser preenchido pelos professores)

**Avaliador 1:** __________________________  
**Status:** [ ] Aprovado  [ ] Ajustar

Observações:

---

**Avaliador 2:** __________________________  
**Status:** [ ] Aprovado  [ ] Ajustar

Observações:

---

**Avaliador 3:** __________________________  
**Status:** [ ] Aprovado  [ ] Ajustar

Observações:

