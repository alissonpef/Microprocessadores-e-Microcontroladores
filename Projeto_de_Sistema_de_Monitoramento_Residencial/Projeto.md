# Projeto de Sistema de Monitoramento Residencial (UFSC)

Este repositório contém o código-fonte para um projeto de Sistema de Monitoramento Residencial desenvolvido como parte da disciplina de Microprocessadores e Microcontroladores na Universidade Federal de Santa Catarina - UFSC.

## Descrição do Projeto

O Sistema de Monitoramento Residencial é um projeto de automação residencial que realiza o controle de temperatura e detecção de gás, proporcionando um ambiente mais seguro e confortável. O código-fonte está desenvolvido em linguagem C para um microcontrolador PIC16F877A.

## Funcionalidades Principais

1. **Controle de Temperatura:**
   - O sistema monitora a temperatura ambiente e ajusta ativamente dispositivos de aquecimento e resfriamento para manter a temperatura desejada.

2. **Detecção de Gás:**
   - Um sensor de gás verifica a presença de gás no ambiente, fornecendo alertas visuais no LCD e por meio de um LED.

3. **Interface de Usuário:**
   - Utiliza um display LCD para fornecer informações sobre a temperatura e o estado da detecção de gás.

4. **Segurança:**
   - Implementa medidas de segurança ao lidar com dispositivos de aquecimento e detecção de gás.

## Autores

- Alisson Pereira Ferreira (Matrícula: 22250769, E-mail: alissonpef@gmail.com)
- Dennis Paul Paz Lopez (Matrícula: 22250970, E-mail: dppazlopez@gmail.com)

## Contato

Para dúvidas ou informações adicionais, entre em contato com os autores do projeto.

## Configuração do Projeto

### Hardware
- Microcontrolador: PIC16F877A
- Componentes adicionais: LCD, sensor de temperatura, sensor de gás, lâmpada, ventilador, LED.

### Software
- Ambiente de Desenvolvimento: MikroC
- Bibliotecas: Sensor de Gás

## Instruções de Uso

1. **Configuração do Hardware:**
   - Conecte os sensores de temperatura e gás, o LCD, e os dispositivos de controle ao microcontrolador conforme descrito no código.

2. **Configuração do Software:**
   - Utilize Proteus para abrir o projeto.
   - Carregue o código no microcontrolador.

3. **Execução:**
   - Alimente o sistema e observe as leituras no LCD.
   - O sistema ajustará ativamente a temperatura com base nas condições ambientais e exibirá mensagens sobre a detecção de gás.

## Lógica do Código

O código fonte está organizado da seguinte maneira:
- A lógica de controle de temperatura é baseada em leituras do sensor de temperatura.
- O sensor de gás é monitorado para detecção de gás no ambiente.
- O LCD e o LED são usados para fornecer feedback visual sobre o estado do sistema.

## Universidade Federal de Santa Catarina*


Curso: Engenharia de Computação.  

Disciplina: Microprocessadores e Microcontroladores.

Professor: Rodrigo Vinícius Mendonça Pereira.
