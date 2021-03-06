#ifndef QREDIS_LEXER_H
#define QREDIS_LEXER_H

#include <QIODevice>
#include <QObject>

namespace QRedis
{
    class Lexer : public QObject
    {
        Q_OBJECT

        public:

            Lexer(QIODevice *, QObject * = 0);
            virtual ~Lexer();

        Q_SIGNALS:

            void character(char);
            void unsafeString(const QString &);
            void safeString(const QByteArray &);

        private Q_SLOTS:

            void readData();

        private:

            bool readCharacter();
            bool readLength();
            bool readUnsafeString();
            bool readSafeString();

            QIODevice * device;
            QByteArray buffer;

            enum {
                DoingNothing,
                ReadingLength,
                ReadingUnsafeString,
                ReadingSafeString
            } state;

            int crlf;
            int length;
    };
}

#endif // QREDIS_LEXER_H
