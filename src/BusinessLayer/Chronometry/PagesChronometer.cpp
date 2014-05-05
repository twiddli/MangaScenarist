#include "PagesChronometer.h"

#include <DataLayer/DataStorageLayer/StorageFacade.h>
#include <DataLayer/DataStorageLayer/SettingsStorage.h>

using namespace DataStorageLayer;
using namespace BusinessLogic;


PagesChronometer::PagesChronometer()
{
}

QString PagesChronometer::name() const
{
	return "pages-chronometer";
}

float PagesChronometer::calculateFrom(
		BusinessLogic::ScenarioTextBlockStyle::Type _type, const QString& _text) const
{
	//
	// Не включаем в хронометраж непечатный текст, заголовок и окончание папки
	//
	if (_type == ScenarioTextBlockStyle::NoprintableText
		|| _type == ScenarioTextBlockStyle::FolderHeader
		|| _type == ScenarioTextBlockStyle::FolderFooter) {
		return 0;
	}

	//
	// Получим значение длительности одной страницы текста
	//
	static const QString SECONDS_KEY = "chronometry/pages/seconds";
	int seconds =
			StorageFacade::settingsStorage()->value(
				SECONDS_KEY,
				SettingsStorage::ApplicationSettings)
			.toInt();

	//
	// Высчитываем длительность строки на странице, из расчёта что на одной странице - 50 строк
	//
	const float LINES_IN_PAGE = 50;
	const float LINE_CHRON = seconds / LINES_IN_PAGE;

	//
	// Длина строки в зависимости от типа
	//
	int lineLength = 0;

	//
	// Количество дополнительных строк
	// По-умолчанию равно единице, чтобы учесть отступ перед блоком
	//
	int additionalLines = 1;

	switch (_type) {
		case ScenarioTextBlockStyle::Character: {
			lineLength = 31;
			break;
		}

		case ScenarioTextBlockStyle::Dialog: {
			lineLength = 28;
			additionalLines = 0;
			break;
		}

		case ScenarioTextBlockStyle::Parenthetical: {
			lineLength = 18;
			additionalLines = 0;
			break;
		}

		case ScenarioTextBlockStyle::Title: {
			lineLength = 18;
			break;
		}

		default: {
			lineLength = 60;
			break;
		}
	}

	//
	// Подсчитаем хронометраж
	//
	float textChron = (float)(linesInText(_text, lineLength) + additionalLines) * LINE_CHRON;
	return textChron;
}

int PagesChronometer::linesInText(const QString& _text, int _lineLength) const
{
	//
	// Переносы не должны разрывать текст
	//

	return _text.length() / _lineLength + ((_text.length() % _lineLength > 0) ? 1 : 0);
}
