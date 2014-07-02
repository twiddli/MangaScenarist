#ifndef RTFEXPORTER_H
#define RTFEXPORTER_H

#include "AbstractExporter.h"

#include <BusinessLayer/ScenarioDocument/ScenarioStyle.h>

#include <QString>


namespace BusinessLogic
{
	/**
	 * @brief Экспортер в RTF
	 */
	class RtfExporter : public AbstractExporter
	{
	public:
		RtfExporter();

		/**
		 * @brief Экспорт заданного документа в указанный файл
		 */
		void exportTo(QTextDocument* _document, const QString& _toFile) const;

	private:
		/**
		 * @brief Преамбула RTF-файла
		 */
		QString header() const;

		/**
		 * @brief RTF стиль текущего блока
		 */
		QString style(ScenarioBlockStyle::Type _type) const;

		/**
		 * @brief Перевести UTF-строку в коды для RTF-формата
		 */
		QString stringToUtfCode(const QString& _text) const;
	};
}

#endif // RTFEXPORTER_H
