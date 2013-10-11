#include<iostream>
#include "audio.h"


SDL_AudioSpec* Audio::audio_spec_obtido = NULL;
Uint8* Audio::bufferAudio = 0;
int Audio::size = 0;
int Audio::position = 0;
bool Audio::isPlaying = false;
int Audio::volume = 5;
int Audio::volumeAntigo = 5;
int Audio::volumeMixado = volume*(SDL_MIX_MAXVOLUME / 10);

void Audio::aumentaVolume()
{
	if(volume<10)
	{
		volume++;
		volumeAntigo = volume -1;
	}
}

void Audio::abaixaVolume()
{
	if(volume>0)
	{	
		volume--;
		volumeAntigo = volume+1;
	}
}

void Audio::mute(bool estado)
{
	if(estado)
	{
		volumeAntigo = volume;
		volume = 0;
	}
	else
	{
		volume = volumeAntigo;
		volumeAntigo = 0;
	}
}

//inicializa o SDL Audio
void Audio::init()
{
	SDL_AudioSpec desired, *obtained;
	desired.freq = FREQUENCIA;
	desired.format = AUDIO_S16SYS;
	desired.channels = NUM_CANAIS;
	desired.samples = SIZE_SAMPLE;
	desired.callback = Audio::callback;
	
	obtained = (SDL_AudioSpec*) malloc(sizeof(SDL_AudioSpec));
	if(obtained == NULL){
		cout << "erro ao inicializar o som! Pouca memoria para alocar espaco para o audioSpec" << endl;
		return ;
	}
	
	if(SDL_OpenAudio(&desired, obtained) < 0){
		cout << "Erro ao inicializar o som:" + string(SDL_GetError()) << endl;
		return ;
	}
		
	audio_spec_obtido = obtained;
}

//Alimenta o controlador da placa de audio com blocos de dados de tempos em tempos. Deve carregar as novas amostras quando solicitado, mixar o som no buffer e atualizar a posição do playback
void Audio::callback(void *userdata, Uint8 *audioFinal, int TamanhoBuffer)
{
	//inicializa o audio final
	memset(audioFinal, 0, TamanhoBuffer);

	//se a posição do cursor da musica for -1 (não inicializado) ou maior que o tamanho da msuica, termina a execução
	if (position == -1 || position >= size)
		return;

	int tamanho_prox_amostra;

	//verifica quantos bytes serão colocados na próxima amostra, o máximo que cabe ou só o quanto falta pra acabar
	if (position + TamanhoBuffer > size)
		tamanho_prox_amostra =  size - position;
	else
		tamanho_prox_amostra = TamanhoBuffer;

	//mixa os dados
	volumeMixado = volume*(SDL_MIX_MAXVOLUME / 10);
	SDL_MixAudio(audioFinal, bufferAudio + position, tamanho_prox_amostra, volumeMixado);

	//muda a posição do cursor
	position += tamanho_prox_amostra;
	if(position >= size)
		position = 0;
}

//realiza todo o processo de carregar a musica especificada e trabalhá-la para que possa ser tocada
void Audio::setAudio(string nome_audio)
{
	//inicializa os valores da classe
	position = -1;
	size = 0;
	bufferAudio = 0;
	isPlaying = false;
	
	//carrego o áudio
	SDL_AudioSpec wavSpec;
	Uint32 wavLen;
	Uint8 *wavBuffer;

	if (SDL_LoadWAV( (nome_audio).c_str() , &wavSpec, &wavBuffer, &wavLen) == NULL){
		cout << "Erro ao inicializar a musica: " + string(SDL_GetError()) << endl;	
		return ;
	}

	//construindo o conversor de áudio para o formato da placa
	SDL_AudioCVT cvt;
	int rc = SDL_BuildAudioCVT(&cvt, wavSpec.format, wavSpec.channels, wavSpec.freq, audio_spec_obtido->format, audio_spec_obtido->channels, audio_spec_obtido->freq);
	if (rc != 0) {
		SDL_FreeWAV(wavBuffer);
		cout << "falha ao converter o audio para o formato da placa de audio: "+string(SDL_GetError()) << endl;
  	}

	//alocando um novo buffer para caso da conversão precisar de um buffer maior
   	cvt.len = wavLen;//o campo len da estrutura AudioCVT deve ser atualizado para o tamanho do buffer do som
    	Uint8 *wavNewBuf = (Uint8 *) malloc(cvt.len * cvt.len_mult);//o novo buffer é alocado
    	if (wavNewBuf == NULL) {
		SDL_FreeWAV(wavBuffer);
		cout << "Sem memoria para um novo buffer!" << endl ;
    	}
    	memcpy(wavNewBuf, wavBuffer, wavLen);//copia os dados no buffer para o novo
    	cvt.buf = wavNewBuf;//aponta o buffer da estrutura do audio convertido para o novo buffer
	//convertendo de fato para o formado da placa
	if ( SDL_ConvertAudio(&cvt) != 0) {
		SDL_FreeWAV(wavBuffer);
		free(wavNewBuf);
		cout << "Erro na conversao do audio!" << endl;
	}
	//como já apontei o buffer da estrutura convertida para o buffer novo, este pode ser liberado
	SDL_FreeWAV(wavBuffer);
	bufferAudio = wavNewBuf;
	
	//setta os valores do áudio nos atributos da classe
	SDL_LockAudio();
	position = 0;
	size = cvt.len * cvt.len_mult;
	SDL_UnlockAudio();
	
	//por fim, toca a bagaça
	SDL_PauseAudio(0);
	isPlaying = true;
}

//para a execução do áudio corrente e libera a memória da musica
void Audio::stopAudio()
{
	//código para faze-lo parar
	if(isPlaying)
		SDL_PauseAudio(1);
	//fecha tudo
	if(bufferAudio)
		SDL_FreeWAV(bufferAudio);
	bufferAudio = NULL;
}

void Audio::closeAudio()
{
	if(audio_spec_obtido)
		free(audio_spec_obtido);
	audio_spec_obtido=NULL;
}

void Audio::setVolume(int volumeRecebido){
	volume = volumeRecebido;
}

int Audio::getVolume(){
	return volume;
}

void Audio::pausaMusica(){
	SDL_PauseAudio(1);	
}
