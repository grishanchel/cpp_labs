#include <memory>
#include <string>
#include <ostream>
#include <list>
#include "task.h"
#include "logged_command_wrapper.h"

/* Курсор влево */

class MoveCursorLeftCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if(editor.HasSelection()) {
            editor.UnselectText();
        }
        else if(cursorPosition != 0) {
            cursorPosition--;
        }
        else if(editor.GetText()[cursorPosition]=='\n'){
            cursorPosition--;
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveCursorLeftCommand(*this);
    }
};

/* Курсор вправо */
class MoveCursorRightCommand : public ICommand {
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if(editor.HasSelection()){
            editor.UnselectText();
        }
        else if(cursorPosition != 0){
            cursorPosition++;
        }
        else if(editor.GetText()[cursorPosition]=='\n'){
            cursorPosition++;
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveCursorRightCommand(*this);
    }

};

/* Курсор вверх */
class MoveCursorUpCommand : public ICommand {

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        int cnt = 0;
        if(cursorPosition==buffer.size()){
            cursorPosition--;
            if (buffer[cursorPosition]=='\n'){
                cursorPosition--;
            }
            while(cursorPosition!=0 && buffer[cursorPosition]!='\n'){
                cursorPosition--;
            }
            if(buffer[cursorPosition]=='\n'){
                cursorPosition++;
            }
            return;
        }

        if(buffer[cursorPosition]=='\n'){
            cursorPosition--;
            cnt++;
        }
        while (buffer[cursorPosition] != '\n' && cursorPosition != 0) {
            cursorPosition--;
            cnt++;
        }
        if (editor.HasSelection())
            editor.UnselectText();

        if (cursorPosition != 0) {
            cursorPosition--;
            while (buffer[cursorPosition] != '\n' && cursorPosition != 0) {
                cursorPosition--;
            }
            if (cursorPosition == 0) {
                cnt--;
            }

            while (cnt != 0) {
                cursorPosition++;
                cnt--;
                if (buffer[cursorPosition] == '\n'){
                    cursorPosition--;
                    return;
                }
            }}
        if (cursorPosition == 0){
            cursorPosition+=cnt;
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveCursorUpCommand(*this);
    }
};

/* Курсор вниз */
class MoveCursorDownCommand : public ICommand {

    size_t GetNextCursorPosition(std::string buffer, size_t cursorPosition) {
        size_t next_cursorPosition = cursorPosition;
        while (next_cursorPosition < buffer.size() && buffer[next_cursorPosition] != '\n'){
            next_cursorPosition++;
        }
        return next_cursorPosition;
    }
    size_t GetPrevCursorPosition(std::string buffer, size_t cursorPosition) {
        if (cursorPosition == 0)
            return 0;
        size_t prev_cursorPosition = cursorPosition - 1;
        if (buffer[prev_cursorPosition] == '\n' && prev_cursorPosition > 1)
            prev_cursorPosition--;
        while (prev_cursorPosition > 0 && buffer[prev_cursorPosition] != '\n'){
            prev_cursorPosition--;
        }
        return prev_cursorPosition;
    }

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        size_t next_cursorPosition = GetNextCursorPosition(buffer, cursorPosition);
        if (next_cursorPosition == buffer.size() - 1)
            cursorPosition = next_cursorPosition;
        else {
            size_t dif = cursorPosition - GetPrevCursorPosition(buffer, cursorPosition);
            size_t next_cursorPosition_2 = GetNextCursorPosition(buffer,  next_cursorPosition + 1);
            if (next_cursorPosition_2 - next_cursorPosition >= dif){
                cursorPosition = next_cursorPosition + dif + 1;
            }
            else {
                cursorPosition = next_cursorPosition_2 - 1;
            }

        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveCursorDownCommand(*this);
    }
};

/* Выделить текст */
class SelectTextCommand : public ICommand {
private:
    size_t selectionSize_;
public:
    SelectTextCommand(size_t selectionSize){
        this->selectionSize_=selectionSize;
    }

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        editor.SelectText(cursorPosition,cursorPosition + selectionSize_);
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitSelectCommand(*this);
    }

};

/* Ввести текст */
class InsertTextCommand : public ICommand {
private:
    std::string text;
public:
    InsertTextCommand(std::string text){
        this->text=text;
    }

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override{
        if(editor.HasSelection()){
            buffer.erase(editor.GetSelection().first, editor.GetSelection().second - editor.GetSelection().first);
            cursorPosition = editor.GetSelection().first;
            editor.UnselectText();
        }
        buffer.insert(cursorPosition,this->text);
        cursorPosition+=this->text.size();

    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitInsertTextCommand(*this);
    }
};

/* Удалить текст */
class DeleteTextCommand : public ICommand {

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if (editor.HasSelection()) {
            buffer.erase(editor.GetSelection().first, editor.GetSelection().second - editor.GetSelection().first);
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitDeleteTextCommand(*this);
    }
};

/* Скопировать текст */
class CopyTextCommand : public ICommand {

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if (editor.HasSelection()) {
            clipboard = buffer.substr(editor.GetSelection().first, editor.GetSelection().second - editor.GetSelection().first);
        } else {
            clipboard = buffer[cursorPosition];
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitCopyTextCommand(*this);
    }
};


/* Вставить скопированный текст */
class PasteTextCommand : public ICommand {

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) {
        if (editor.HasSelection()) {
            buffer.erase(editor.GetSelection().first, editor.GetSelection().second - editor.GetSelection().first);
            editor.UnselectText();
        }
        buffer.insert(cursorPosition, clipboard);
        cursorPosition += clipboard.size();
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitPasteTextCommand(*this);
    }

};

/* Привести выделенный текст в верхний регистр */
class UppercaseTextCommand : public ICommand {

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) {
        if (editor.HasSelection()) {
            for (size_t i = editor.GetSelection().first; i <= editor.GetSelection().second; i++) {
                buffer[i] = toupper(buffer[i]);
            }
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitUppercaseTextCommand(*this);
    }
};

/* Привести выделенный текст в нижний регистр */
class LowercaseTextCommand : public ICommand {

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) {
        if (editor.HasSelection()) {
            for (size_t i = cursorPosition; i <= editor.GetSelection().second; i++) {
                buffer[i] = tolower(buffer[i]);
            }
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitLowercaseTextCommand(*this);
    }
};

/* Перенести курсор в конец строки */
class MoveToEndCommand : public ICommand {

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor){
        while (cursorPosition < buffer.size() && buffer[cursorPosition]!= '\n' ){
            cursorPosition++;
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveToEndCommand(*this);
    }

};

/* Перенести курсор в начало строки */
class MoveToStartCommand : public ICommand {

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) {
        if (cursorPosition == 0){
            cursorPosition=0;
        }
        if (buffer[cursorPosition] == '\n' && cursorPosition > 1){
            cursorPosition--;
        }
        while (cursorPosition > 0 && buffer[cursorPosition] != '\n') {
            cursorPosition--;
        }
        if (cursorPosition != 0){
            cursorPosition++;
        }
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveToStartCommand(*this);
    }

};

/* Удалить часть строки, начиная от позиции курсора до первого пробела или конца строки */
class DeleteWordCommand : public ICommand {

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor){
        editor.UnselectText();
        size_t position = 10000000;
        for (size_t i = cursorPosition; i < buffer.size(); i++){
            if (buffer[i] == ' ' || buffer[i] == '\n') {
                position = i;
                break;
            }
        }
        if (position == 10000000) {
            position = buffer.size() - 1;
        }
        buffer.erase(cursorPosition, position - cursorPosition);
    }

    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitDeleteWordCommand(*this);
    }

};

/* Макрос */
class MacroCommand : public ICommand {
private:
    std::list<CommandPtr> subcommands_;
    std::ostream* logStream_;
public:
    MacroCommand(std::list<CommandPtr> subcommands_) {
        this->subcommands_ = subcommands_;
    }

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor){
        for (auto const& command : subcommands_) {
            command->Apply(buffer, cursorPosition, clipboard, editor);

        }

    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        for (auto const& command : subcommands_) {
            command->AcceptVisitor(visitor);
        }
    }
};


/*
 * Указать тип команды, которую надо создать
 * Функция возвращает ссылку на *this, чтобы можно было объединять вызовы методов билдера в цепочку (fluent interface)
 */
CommandBuilder& CommandBuilder::WithType(Type type) {
    this->type_ = type;
    return *this;
}

/*
 * Указать размер выделения. Нужно для создания команды SelectText
 * Функция возвращает ссылку на *this, чтобы можно было объединять вызовы методов билдера в цепочку (fluent interface)
 */
CommandBuilder& CommandBuilder::SelectionSize(size_t selectionSize) {
    this->selectionSize_ = selectionSize;
    return *this;
}

/*
 * Указать текст для ввода. Нужно для создания команды InsertText
 * Функция возвращает ссылку на *this, чтобы можно было объединять вызовы методов билдера в цепочку (fluent interface)
 */
CommandBuilder& CommandBuilder::Text(std::string text) {
    this->text_ = text;
    return *this;
}

/*
 * Включить логирование команды. Используется для оборачивания объекта команды в логирующий декоратор LoggedCommandWrapper
 * Функция возвращает ссылку на *this, чтобы можно было объединять вызовы методов билдера в цепочку (fluent interface)
 */
CommandBuilder& CommandBuilder::LogTo(std::ostream& logStream) {
    this->logStreamPtr_ = &logStream;
    return *this;
}

/*
 * Добавить команду в макрос. Используется для создания команды MacroCommand
 * Функция возвращает ссылку на *this, чтобы можно было объединять вызовы методов билдера в цепочку (fluent interface)
 */
CommandBuilder& CommandBuilder::AddSubcommand(CommandPtr subcommand) {
    this->subcommands_.push_back(subcommand);
    return *this;
}

CommandBuilder::CommandBuilder() {
    this->logStreamPtr_ = nullptr;
    this->selectionSize_ = 0;
    this->subcommands_ = {};
    this->text_="";
}

CommandPtr CommandBuilder::build() {
    std::shared_ptr<ICommand> ptr;

    if (logStreamPtr_ == nullptr) {

        if (this->type_ == CommandBuilder::Type::MoveCursorLeft) {
            ptr = std::shared_ptr<ICommand>(new MoveCursorLeftCommand());
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::MoveCursorRight) {
            ptr = std::shared_ptr<ICommand>(new MoveCursorRightCommand());
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::MoveCursorUp) {
            ptr = std::shared_ptr<ICommand>(new MoveCursorUpCommand());
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::MoveCursorDown) {
            ptr = std::shared_ptr<ICommand>(new MoveCursorDownCommand());
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::SelectText) {
            ptr = std::shared_ptr<ICommand>(new SelectTextCommand(this->selectionSize_));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::InsertText) {
            ptr = std::shared_ptr<ICommand>(new InsertTextCommand(this->text_));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::DeleteText) {
            ptr = std::shared_ptr<ICommand>(new DeleteTextCommand());
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::CopyText) {
            ptr = std::shared_ptr<ICommand>(new CopyTextCommand());
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::PasteText) {
            ptr = std::shared_ptr<ICommand>(new PasteTextCommand());
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::UppercaseText) {
            ptr = std::shared_ptr<ICommand>(new UppercaseTextCommand());
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::LowercaseText) {
            ptr = std::shared_ptr<ICommand>(new LowercaseTextCommand());
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::MoveToEnd) {
            ptr = std::shared_ptr<ICommand>(new MoveToEndCommand());
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::MoveToStart) {
            ptr = std::shared_ptr<ICommand>(new MoveToStartCommand());
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::DeleteWord) {
            ptr = std::shared_ptr<ICommand>(new DeleteWordCommand());
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::Macro) {
            ptr = std::shared_ptr<ICommand>(new MacroCommand(this->subcommands_));
            return ptr;
        }
    } else {

        if (this->type_ == CommandBuilder::Type::MoveCursorLeft) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new MoveCursorLeftCommand())));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::MoveCursorRight) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new MoveCursorRightCommand())));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::MoveCursorUp) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new MoveCursorUpCommand())));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::MoveCursorDown) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new MoveCursorDownCommand())));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::SelectText) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new SelectTextCommand(this->selectionSize_))));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::InsertText) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new InsertTextCommand(this->text_))));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::DeleteText) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new DeleteTextCommand())));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::CopyText) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new CopyTextCommand())));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::PasteText) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new PasteTextCommand())));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::UppercaseText) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new UppercaseTextCommand())));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::LowercaseText) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new LowercaseTextCommand())));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::MoveToEnd) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new MoveToEndCommand())));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::MoveToStart) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new MoveToStartCommand())));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::DeleteWord) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new DeleteWordCommand())));
            return ptr;
        }
        if (this->type_ == CommandBuilder::Type::Macro) {
            ptr = std::shared_ptr<ICommand>(new LoggedCommandWrapper(*logStreamPtr_,std::shared_ptr<ICommand>(new MacroCommand(this->subcommands_))));
            return ptr;
        }
    }
    return ptr; 
}


CommandLoggerVisitor::CommandLoggerVisitor(std::ostream& logStream): logStream_(logStream) {}

void CommandLoggerVisitor::VisitMoveCursorLeftCommand(MoveCursorLeftCommand& command) {
    this->logStream_ << "h";
}
void CommandLoggerVisitor::VisitMoveCursorRightCommand(MoveCursorRightCommand& command) {
    this->logStream_ << "l";
}
void CommandLoggerVisitor::VisitMoveCursorUpCommand(MoveCursorUpCommand& command) {
    this->logStream_ << "k";
}
void CommandLoggerVisitor::VisitMoveCursorDownCommand(MoveCursorDownCommand& command) {
    this->logStream_ << "j";
}
void CommandLoggerVisitor::VisitSelectCommand(SelectTextCommand& command) {
    this->logStream_ << "v";
}
void CommandLoggerVisitor::VisitInsertTextCommand(InsertTextCommand& command) {
    this->logStream_ << "i";
}
void CommandLoggerVisitor::VisitDeleteTextCommand(DeleteTextCommand& command) {
    this->logStream_ << "d";
}
void CommandLoggerVisitor::VisitCopyTextCommand(CopyTextCommand& command) {
    this->logStream_ << "y";
}
void CommandLoggerVisitor::VisitPasteTextCommand(PasteTextCommand& command) {
    this->logStream_ << "p";
}
void CommandLoggerVisitor::VisitUppercaseTextCommand(UppercaseTextCommand& command) {
    this->logStream_ << "U";
}
void CommandLoggerVisitor::VisitLowercaseTextCommand(LowercaseTextCommand& command) {
    this->logStream_ << "u";
}
void CommandLoggerVisitor::VisitMoveToEndCommand(MoveToEndCommand& command) {
    this->logStream_ << "$";
}
void CommandLoggerVisitor::VisitMoveToStartCommand(MoveToStartCommand& command) {
    this->logStream_ << "0";
}
void CommandLoggerVisitor::VisitDeleteWordCommand(DeleteWordCommand& command) {
    this->logStream_ << "dE";
}





